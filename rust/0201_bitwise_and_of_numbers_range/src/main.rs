struct Solution;

impl Solution {
    pub fn range_bitwise_and(left: i32, right: i32) -> i32 {
        if left == right {
            return left;
        }

        let mut diff = right - left;
        let mut count = 0;
        while diff > 0 {
            count += 1;
            diff >>= 1;
        }

        if count >= 31 {
            return 0;
        }

        let left = left >> count;
        let right = right >> count;
        let mut result = left;
        for i in left..=right {
            result &= i;
        }

        result << count
    }
}

fn main() {
    let left = 5;
    let right = 7;

    let result = Solution::range_bitwise_and(left, right);

    println!("{}", result);
}
