struct Solution;

impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        let len = nums.len();

        if nums.is_empty() {
            return 0;
        }

        if len == 1 {
            return nums[0];
        }

        if len == 2 {
            if nums[0] > nums[1] {
                return nums[0];
            } else {
                return nums[1];
            }
        }

        let mut sums1 = vec![0; len];
        let mut sums2 = vec![0; len];

        for i in 0..len - 1 {
            if i >= 2 {
                sums1[i] = sums1[i - 2] + nums[i];
            } else {
                sums1[i] = nums[i];
            }
            if i >= 3 {
                sums1[i] = sums1[i].max(sums1[i - 3] + nums[i]);
            }
        }

        for i in 1..len {
            if i >= 2 {
                sums2[i] = sums2[i - 2] + nums[i];
            } else {
                sums2[i] = nums[i];
            }
            if i >= 3 {
                sums2[i] = sums2[i].max(sums2[i - 3] + nums[i]);
            }
        }

        [
            sums1[len - 2],
            sums1[len - 3],
            sums2[len - 1],
            sums2[len - 2],
        ]
        .into_iter()
        .max()
        .unwrap()
    }
}

fn main() {
    let nums = vec![200, 3, 140, 20, 10];

    let result = Solution::rob(nums);

    println!("{}", result);
}
