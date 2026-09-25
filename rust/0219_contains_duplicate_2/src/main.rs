struct Solution;

impl Solution {
    pub fn contains_nearby_duplicate(nums: Vec<i32>, k: i32) -> bool {
        use std::collections::HashMap;

        let mut set = HashMap::new();
        for (i, n) in nums.iter().enumerate() {
            if set.contains_key(n) && i as i32 - set[n] <= k {
                return true;
            }
            set.insert(*n, i as i32);
        }

        false
    }
}

fn main() {
    let nums = vec![1, 2, 3, 1, 2, 3];
    let k = 2;

    let result = Solution::contains_nearby_duplicate(nums, k);

    println!("{}", result);
}
