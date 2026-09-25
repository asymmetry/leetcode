struct Solution;

impl Solution {
    pub fn contains_duplicate(nums: Vec<i32>) -> bool {
        use std::collections::HashSet;

        let mut set = HashSet::new();
        for n in nums.iter() {
            if set.contains(n) {
                return true;
            }
            set.insert(*n);
        }

        false
    }
}

fn main() {
    let nums = vec![1, 2, 3, 1];

    let result = Solution::contains_duplicate(nums);

    println!("{}", result);
}
