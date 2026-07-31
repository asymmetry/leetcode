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
    pub fn remove_elements(mut head: Option<Box<ListNode>>, val: i32) -> Option<Box<ListNode>> {
        let mut out = None;
        let mut out_mut = &mut out;

        while let Some(mut node) = head {
            if node.val != val {
                head = node.next.take();
                out_mut = &mut out_mut.insert(node).next;
            } else {
                head = node.next.take();
            }
        }

        out
    }
}

fn main() {
    let nums = vec![1, 2, 6, 3, 4, 5, 6];
    let head = create_list(&nums);

    let result = Solution::remove_elements(head, 6);

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
