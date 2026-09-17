struct Solution;

impl Solution {
    pub fn min_sub_array_len(target: i32, nums: Vec<i32>) -> i32 {
        if nums.len() == 1 {
            if nums[0] >= target {
                return 1;
            } else {
                return 0;
            }
        }

        let mut l = 0;
        let mut r = 0;
        let mut sum = 0;
        let mut min_length = usize::MAX;

        while r < nums.len() {
            sum += nums[r];
            r += 1;

            while sum >= target && l < r {
                min_length = min_length.min(r - l);
                sum -= nums[l];
                l += 1;
            }
        }

        if min_length == usize::MAX {
            0
        } else {
            min_length as i32
        }
    }
}

fn main() {
    let target = 11;
    let nums = vec![1, 1, 1, 1, 1, 1, 1, 1];

    let result = Solution::min_sub_array_len(target, nums);

    println!("{}", result);
}
