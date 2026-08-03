#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

fn create_list(nums: &[i32]) -> Option<Box<ListNode>> {
    let mut head = None;
    for &num in nums.iter().rev() {
        let mut node = Box::new(ListNode::new(num));
        node.next = head;
        head = Some(node);
    }
    head
}

struct Solution;

impl Solution {
    pub fn reverse_list(mut head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut out = None;
        let out_mut = &mut out;

        while let Some(mut node) = head {
            head = node.next.take();

            let done = out_mut.take();
            node.next = done;

            let _ = out_mut.insert(node);
        }

        out
    }
}

fn main() {
    let nums = vec![1, 2, 3, 4, 5];
    let head = create_list(&nums);

    let result = Solution::reverse_list(head);

    print!("[");
    let mut current = &result;
    while let Some(node) = current {
        print!("{}", node.val);
        current = &node.next;
        if current.is_some() {
            print!(",");
        }
    }
    println!("]");
}
