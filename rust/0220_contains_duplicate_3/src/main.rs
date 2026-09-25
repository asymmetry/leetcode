struct Solution;

impl Solution {
    pub fn contains_nearby_almost_duplicate(
        nums: Vec<i32>,
        index_diff: i32,
        value_diff: i32,
    ) -> bool {
        use std::collections::{HashMap, HashSet};

        let mut buckets = HashMap::<i32, HashSet<i32>>::new();

        for (i, n) in nums.iter().enumerate() {
            let i = i as i32;
            if i > index_diff {
                let index = (i - index_diff - 1) as usize;
                let bucket_id = nums[index].div_euclid(value_diff + 1);
                buckets.get_mut(&bucket_id).unwrap().remove(&nums[index]);
            }

            let bucket_id = n.div_euclid(value_diff + 1);
            if let Some(bucket) = buckets.get(&bucket_id)
                && !bucket.is_empty()
            {
                return true;
            }
            if let Some(bucket) = buckets.get(&(bucket_id + 1)) {
                for m in bucket {
                    if (m - n).abs() <= value_diff {
                        return true;
                    }
                }
            }
            if let Some(bucket) = buckets.get(&(bucket_id - 1)) {
                for m in bucket {
                    if (m - n).abs() <= value_diff {
                        return true;
                    }
                }
            }

            buckets.entry(bucket_id).or_default().insert(*n);
        }

        false
    }
}

fn main() {
    let nums = vec![1, 2, 3, 1];
    let index_diff = 3;
    let value_diff = 0;

    let result = Solution::contains_nearby_almost_duplicate(nums, index_diff, value_diff);

    println!("{:?}", result);
}
