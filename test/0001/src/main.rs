// Async logger

use std::collections::VecDeque;
use std::io::Write;
use std::sync::{Arc, Condvar, Mutex};
use std::thread::{self, JoinHandle};

struct AsyncLoggerState {
    pub buffer: VecDeque<String>,
    pub stopped: bool,
    pub writing: bool,
}

struct AsyncLoggerInner {
    pub state: Mutex<AsyncLoggerState>,
    pub cv: Condvar,
}

// log() pushes the message to a queue and returns immediately.
// A background thread writes queued messages to `out`, one per line.
pub struct AsyncLogger {
    inner: Arc<AsyncLoggerInner>,
    handle: Option<JoinHandle<()>>,
}

impl AsyncLogger {
    pub fn new<W: Write + Send + 'static>(mut out: W) -> Self {
        let inner = Arc::new(AsyncLoggerInner {
            state: Mutex::new(AsyncLoggerState {
                buffer: VecDeque::new(),
                stopped: false,
                writing: false,
            }),
            cv: Condvar::new(),
        });
        let rx = inner.clone();
        let handle = std::thread::spawn(move || {
            loop {
                let out_s = {
                    let mut state = rx.state.lock().unwrap();
                    while state.buffer.is_empty() && !state.stopped {
                        state = rx.cv.wait(state).unwrap();
                    }
                    if state.buffer.is_empty() && state.stopped {
                        return;
                    }
                    state.writing = true;
                    state.buffer.pop_front().unwrap()
                };

                let _ = writeln!(&mut out, "{}", out_s);
                let _ = out.flush();

                {
                    let mut state = rx.state.lock().unwrap();
                    state.writing = false;
                }
                rx.cv.notify_all();
            }
        });
        Self {
            inner,
            handle: Some(handle),
        }
    }

    pub fn log(&self, msg: &str) {
        {
            let mut state = self.inner.state.lock().unwrap();
            if state.stopped {
                return;
            }
            state.buffer.push_back(msg.to_string());
        }
        self.inner.cv.notify_all();
    }

    pub fn flush(&self) {
        let mut state = self.inner.state.lock().unwrap();
        while !state.buffer.is_empty() || state.writing {
            state = self.inner.cv.wait(state).unwrap();
        }
    }

    pub fn stop(&mut self) {
        if let Some(handle) = self.handle.take() {
            {
                let mut state = self.inner.state.lock().unwrap();
                state.stopped = true;
            }
            self.inner.cv.notify_all();
            handle.join().unwrap();
        }
    }
}

// Writes everything still queued, then stops the thread.
impl Drop for AsyncLogger {
    fn drop(&mut self) {
        self.stop();
    }
}

// In-memory writer the tests can read back after giving a clone to the logger.
#[derive(Clone, Default)]
struct SharedBuf(Arc<Mutex<Vec<u8>>>);

impl Write for SharedBuf {
    fn write(&mut self, data: &[u8]) -> std::io::Result<usize> {
        self.0.lock().unwrap().extend_from_slice(data);
        Ok(data.len())
    }

    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}

impl SharedBuf {
    fn lines(&self) -> Vec<String> {
        let buf = self.0.lock().unwrap();
        String::from_utf8_lossy(&buf)
            .lines()
            .map(String::from)
            .collect()
    }
}

fn main() {
    // 1. Single thread: all messages written, in order.
    {
        let out = SharedBuf::default();
        let logger = AsyncLogger::new(out.clone());
        for i in 0..100 {
            logger.log(&format!("msg {i}"));
        }
        logger.flush();

        let got = out.lines();
        assert_eq!(got.len(), 100);
        for (i, line) in got.iter().enumerate() {
            assert_eq!(*line, format!("msg {i}"));
        }
    }

    // 2. Multiple threads: nothing lost.
    {
        let out = SharedBuf::default();
        let logger = AsyncLogger::new(out.clone());
        thread::scope(|s| {
            for t in 0..4 {
                let logger = &logger;
                s.spawn(move || {
                    for i in 0..1000 {
                        logger.log(&format!("{t}:{i}"));
                    }
                });
            }
        });
        logger.flush();

        assert_eq!(out.lines().len(), 4000);
    }

    // 3. Drop writes whatever is still queued.
    {
        let out = SharedBuf::default();
        {
            let logger = AsyncLogger::new(out.clone());
            for _ in 0..500 {
                logger.log("x");
            }
        }
        assert_eq!(out.lines().len(), 500);
    }

    // 4. stop() writes what's queued, and calling it twice is fine.
    {
        let out = SharedBuf::default();
        let mut logger = AsyncLogger::new(out.clone());
        logger.log("a");
        logger.log("b");
        logger.stop();
        logger.stop();
        assert_eq!(out.lines(), vec!["a", "b"]);
    }

    println!("All tests passed");
}
