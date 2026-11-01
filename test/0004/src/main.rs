// Pub/sub channel

use std::sync::{
    Arc, Mutex,
    atomic::{AtomicBool, AtomicUsize, Ordering},
    mpsc,
};
use std::thread;
use std::time::Duration;

// One subscription to a Channel, created by Channel::subscribe(). One thread
// calls recv at a time. It may outlive the Channel.
pub struct Subscriber<T> {
    rx: mpsc::Receiver<Arc<T>>,
    pub(crate) index: usize,
}

unsafe impl<T> Sync for Subscriber<T> where T: Send {}

impl<T> Subscriber<T> {
    pub fn new(rx: mpsc::Receiver<Arc<T>>, index: usize) -> Self {
        Self { rx, index }
    }

    // Blocks while there is no unread message. Returns None once every queued
    // message has been read and the channel is closed or this subscriber has
    // unsubscribed.
    pub fn recv(&self) -> Option<Arc<T>> {
        self.rx.recv().ok()
    }
}

// Broadcast channel shared by any number of publisher threads. Every subscriber
// gets every message published after it subscribed and before it unsubscribed.
// Each message is one object shared by all of them, never cloned, and dropped
// when the last holder lets go. All subscribers see the messages in the same
// order. Queues are unbounded, so a slow subscriber never holds up publishers
// or other subscribers.
pub struct Channel<T> {
    inner: Arc<Mutex<ChannelInner<T>>>,
    next_index: AtomicUsize,
}

struct ChannelInner<T> {
    senders: Vec<(mpsc::Sender<Arc<T>>, usize)>,
    closed: bool,
}

impl<T> Channel<T> {
    #[allow(clippy::new_without_default)]
    pub fn new() -> Self {
        Self {
            inner: Arc::new(Mutex::new(ChannelInner {
                senders: Vec::new(),
                closed: false,
            })),
            next_index: AtomicUsize::new(0),
        }
    }

    // Subscribing to a closed channel gives a subscriber with nothing to read.
    pub fn subscribe(&self) -> Subscriber<T> {
        let (tx, rx) = mpsc::channel::<Arc<T>>();
        let index = self.next_index.fetch_add(1, Ordering::Relaxed);
        let mut inner = self.inner.lock().unwrap();
        if !inner.closed {
            inner.senders.push((tx, index));
        }
        Subscriber::new(rx, index)
    }

    // Stops new messages from being queued for the subscriber and wakes a
    // blocked recv on it. The subscriber can still read what is already queued.
    // May be called from any thread. Does nothing if `sub` already unsubscribed
    // or belongs to another channel. Works on a closed channel.
    pub fn unsubscribe(&self, sub: &Subscriber<T>) {
        let mut inner = self.inner.lock().unwrap();
        inner.senders.retain(|(_, i)| sub.index != *i);
    }

    // Never blocks. With no subscribers the message is discarded. Returns the
    // value back if the channel is closed.
    pub fn publish(&self, value: T) -> Result<(), T> {
        if self.inner.lock().unwrap().closed {
            return Err(value);
        }

        let value = Arc::new(value);
        let mut inner = self.inner.lock().unwrap();
        inner
            .senders
            .retain(|(s, _)| !s.send(value.clone()).is_err());
        Ok(())
    }

    // Rejects new messages and wakes every blocked recv. Subscribers can still
    // read what is already queued. Calling it again does nothing.
    pub fn close(&self) {
        let mut inner = self.inner.lock().unwrap();
        inner.closed = true;
        inner.senders.clear();
    }
}

// Long enough that a thread which should block has clearly blocked.
const WAIT: Duration = Duration::from_millis(50);

fn main() {
    // 1. Broadcast: every subscriber gets every message in order, even when
    // nobody reads until publishing has finished.
    {
        let ch = Channel::new();
        let subs: Vec<_> = (0..3).map(|_| ch.subscribe()).collect();
        for i in 0..1000 {
            assert_eq!(ch.publish(i), Ok(()));
        }
        for sub in &subs {
            for i in 0..1000 {
                assert_eq!(sub.recv(), Some(Arc::new(i)));
            }
        }
    }

    // 2. Late subscribers only get messages published after they subscribed,
    // and a message with no subscribers is discarded.
    {
        let ch = Channel::new();
        ch.publish(1).unwrap();
        let first = ch.subscribe();
        ch.publish(2).unwrap();
        let second = ch.subscribe();
        ch.publish(3).unwrap();
        ch.close();
        assert_eq!(first.recv(), Some(Arc::new(2)));
        assert_eq!(first.recv(), Some(Arc::new(3)));
        assert_eq!(first.recv(), None);
        assert_eq!(second.recv(), Some(Arc::new(3)));
        assert_eq!(second.recv(), None);
    }

    // 3. Blocking: recv waits for a message, and a subscriber that never reads
    // holds nobody up.
    {
        let ch = Channel::new();
        let idle = ch.subscribe();
        let sub = ch.subscribe();
        let received = AtomicBool::new(false);
        thread::scope(|s| {
            let consumer = s.spawn(|| {
                let value = sub.recv();
                received.store(true, Ordering::SeqCst);
                value
            });
            thread::sleep(WAIT);
            assert!(!received.load(Ordering::SeqCst));
            ch.publish(7).unwrap();
            assert_eq!(consumer.join().unwrap(), Some(Arc::new(7)));
        });
        assert_eq!(idle.recv(), Some(Arc::new(7)));
    }

    // 4. Many publishers and subscribers: nothing lost or duplicated, each
    // publisher's messages stay in order, and all subscribers see the same
    // order.
    {
        const PUBLISHERS: usize = 4;
        const SUBSCRIBERS: usize = 4;
        const N: usize = 10_000; // per publisher
        let ch = Channel::new();
        let subs: Vec<_> = (0..SUBSCRIBERS).map(|_| ch.subscribe()).collect();
        let ch = &ch;
        let received: Vec<Vec<(usize, usize)>> = thread::scope(|s| {
            let consumers: Vec<_> = subs
                .into_iter()
                .map(|sub| {
                    s.spawn(move || {
                        let mut got = Vec::new();
                        while let Some(message) = sub.recv() {
                            got.push(*message);
                        }
                        got
                    })
                })
                .collect();
            let publishers: Vec<_> = (0..PUBLISHERS)
                .map(|p| {
                    s.spawn(move || {
                        for i in 0..N {
                            ch.publish((p, i)).unwrap();
                        }
                    })
                })
                .collect();
            for publisher in publishers {
                publisher.join().unwrap();
            }
            ch.close();
            consumers.into_iter().map(|c| c.join().unwrap()).collect()
        });

        assert_eq!(received[0].len(), PUBLISHERS * N);
        let mut next = [0; PUBLISHERS];
        for &(p, i) in &received[0] {
            assert_eq!(i, next[p], "publisher {p} out of order");
            next[p] += 1;
        }
        for got in &received {
            assert!(got == &received[0], "subscribers disagree on the order");
        }
    }

    // 5. Subscribers can come and go while publishers are running, leaving
    // either by unsubscribing or by being dropped.
    {
        let ch = Channel::new();
        let done = AtomicBool::new(false);
        thread::scope(|s| {
            for _ in 0..2 {
                s.spawn(|| {
                    let mut i = 0;
                    while !done.load(Ordering::SeqCst) {
                        ch.publish(i).unwrap();
                        i += 1;
                    }
                });
            }
            let churners: Vec<_> = (0..2)
                .map(|_| {
                    s.spawn(|| {
                        for round in 0..1000 {
                            let sub = ch.subscribe();
                            assert!(sub.recv().is_some());
                            if round % 2 == 0 {
                                ch.unsubscribe(&sub);
                            }
                        }
                    })
                })
                .collect();
            for churner in churners {
                churner.join().unwrap();
            }
            done.store(true, Ordering::SeqCst);
        });
    }

    // 6. Close: rejects new messages, lets subscribers read the rest, and wakes
    // every blocked recv.
    {
        let ch = Channel::new();
        let sub = ch.subscribe();
        ch.publish(1).unwrap();
        ch.publish(2).unwrap();
        ch.close();
        ch.close();
        assert_eq!(ch.publish(3), Err(3));
        assert_eq!(sub.recv(), Some(Arc::new(1)));
        assert_eq!(sub.recv(), Some(Arc::new(2)));
        assert_eq!(sub.recv(), None);
        assert_eq!(sub.recv(), None);

        let late = ch.subscribe();
        assert_eq!(late.recv(), None);
    }
    {
        let ch = Channel::<i32>::new();
        let a = ch.subscribe();
        let b = ch.subscribe();
        let consumer_a = thread::spawn(move || a.recv());
        let consumer_b = thread::spawn(move || b.recv());
        thread::sleep(WAIT);
        ch.close();
        assert_eq!(consumer_a.join().unwrap(), None);
        assert_eq!(consumer_b.join().unwrap(), None);
    }

    // 7. Dropping the channel closes it, and subscribers can outlive it.
    {
        let ch = Channel::new();
        let sub = ch.subscribe();
        ch.publish(1).unwrap();
        drop(ch);
        assert_eq!(sub.recv(), Some(Arc::new(1)));
        assert_eq!(sub.recv(), None);
    }
    {
        let ch = Channel::<i32>::new();
        let sub = ch.subscribe();
        let consumer = thread::spawn(move || sub.recv());
        thread::sleep(WAIT);
        drop(ch);
        assert_eq!(consumer.join().unwrap(), None);
    }

    // 8. Unsubscribe: queued messages can still be read, new ones never arrive,
    // other subscribers carry on, and calling it again does nothing.
    {
        let ch = Channel::new();
        let a = ch.subscribe();
        let b = ch.subscribe();
        ch.publish(1).unwrap();
        ch.unsubscribe(&a);
        ch.unsubscribe(&a);
        ch.publish(2).unwrap();
        assert_eq!(a.recv(), Some(Arc::new(1)));
        assert_eq!(a.recv(), None);
        assert_eq!(a.recv(), None);
        assert_eq!(b.recv(), Some(Arc::new(1)));
        assert_eq!(b.recv(), Some(Arc::new(2)));
    }
    // It wakes this subscriber's blocked recv, but no other subscriber's.
    {
        let ch = Channel::new();
        let a = ch.subscribe();
        let b = ch.subscribe();
        let b_returned = AtomicBool::new(false);
        thread::scope(|s| {
            let consumer_a = s.spawn(|| a.recv());
            let consumer_b = s.spawn(|| {
                let value = b.recv();
                b_returned.store(true, Ordering::SeqCst);
                value
            });
            thread::sleep(WAIT);
            ch.unsubscribe(&a);
            assert_eq!(consumer_a.join().unwrap(), None);
            thread::sleep(WAIT);
            assert!(!b_returned.load(Ordering::SeqCst));
            ch.publish(7).unwrap();
            assert_eq!(consumer_b.join().unwrap(), Some(Arc::new(7)));
        });
    }
    // It works on a closed channel, and a subscriber of another channel is left
    // alone.
    {
        let ch = Channel::new();
        let other = Channel::new();
        let a = ch.subscribe();
        let b = ch.subscribe();
        ch.publish(1).unwrap();
        other.unsubscribe(&a);
        ch.publish(2).unwrap();
        assert_eq!(a.recv(), Some(Arc::new(1)));
        ch.close();
        ch.unsubscribe(&a);
        assert_eq!(a.recv(), Some(Arc::new(2)));
        assert_eq!(a.recv(), None);
        assert_eq!(b.recv(), Some(Arc::new(1)));
        assert_eq!(b.recv(), Some(Arc::new(2)));
        assert_eq!(b.recv(), None);
    }
    // 9. Ownership: subscribers share one object per message, which is dropped
    // when the last holder lets go. A dropped subscriber lets go of its unread
    // messages, whether or not it unsubscribed first. Unsubscribing alone keeps
    // them readable, and later messages never reach it.
    {
        let item = Arc::new(0);
        let ch = Channel::new();
        ch.publish(item.clone()).unwrap();
        assert_eq!(Arc::strong_count(&item), 1);

        let a = ch.subscribe();
        {
            let _b = ch.subscribe();
            ch.publish(item.clone()).unwrap();
            assert_eq!(Arc::strong_count(&item), 2);
            assert!(a.recv().is_some());
            assert_eq!(Arc::strong_count(&item), 2);
        }
        assert_eq!(Arc::strong_count(&item), 1);
        {
            let b = ch.subscribe();
            ch.publish(item.clone()).unwrap();
            assert!(a.recv().is_some());
            ch.unsubscribe(&b);
            assert_eq!(Arc::strong_count(&item), 2);
        }
        assert_eq!(Arc::strong_count(&item), 1);

        ch.publish(item.clone()).unwrap();
        assert_eq!(Arc::strong_count(&item), 2);
        ch.unsubscribe(&a);
        assert_eq!(Arc::strong_count(&item), 2);
        assert!(a.recv().is_some());
        assert_eq!(Arc::strong_count(&item), 1);
        ch.publish(item.clone()).unwrap();
        assert_eq!(Arc::strong_count(&item), 1);
    }

    // 10. Every subscriber gets the same object, so T need not be Clone, and a
    // message outlives the subscriber and channel it came from.
    {
        #[derive(Debug)]
        struct NoClone(i32);

        let (from_a, from_b) = {
            let ch = Channel::new();
            let a = ch.subscribe();
            let b = ch.subscribe();
            ch.publish(NoClone(7)).unwrap();
            (a.recv().unwrap(), b.recv().unwrap())
        };
        assert!(Arc::ptr_eq(&from_a, &from_b));
        assert_eq!(from_a.0, 7);
    }

    println!("All tests passed");
}
