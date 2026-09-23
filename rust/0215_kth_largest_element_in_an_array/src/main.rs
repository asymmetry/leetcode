struct Solution;

impl Solution {
    pub fn find_kth_largest(nums: Vec<i32>, k: i32) -> i32 {
        if nums.is_empty() {
            return 0;
        }

        let pivot = nums[0];
        let mut left = Vec::new();
        let mut mid = Vec::new();
        let mut right = Vec::new();
        for n in nums {
            if n > pivot {
                left.push(n);
            }
            if n == pivot {
                mid.push(n);
            }
            if n < pivot {
                right.push(n);
            }
        }

        if left.len() as i32 >= k {
            Solution::find_kth_largest(left, k)
        } else if left.len() as i32 + mid.len() as i32 >= k {
            pivot
        } else {
            Solution::find_kth_largest(right, k - left.len() as i32 - mid.len() as i32)
        }
    }
}

fn main() {
    let nums = vec![3, 2, 1, 5, 6, 4];
    let k = 2;

    let result = Solution::find_kth_largest(nums, k);

    println!("{}", result);
}
