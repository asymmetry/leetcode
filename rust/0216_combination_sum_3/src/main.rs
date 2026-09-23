struct Solution;

impl Solution {
    pub fn combination_sum3(k: i32, n: i32) -> Vec<Vec<i32>> {
        Solution::combination_sum3_inner(k, n, 1)
    }

    fn combination_sum3_inner(k: i32, n: i32, s: i32) -> Vec<Vec<i32>> {
        if k <= 0 || n < k || s > 9 || s > n {
            return Vec::new();
        }

        if k == 1 {
            if s <= n && n <= 9 {
                return vec![vec![n]];
            } else {
                return Vec::new();
            }
        }

        let mut result = Vec::new();

        for i in s..=n {
            let r = Solution::combination_sum3_inner(k - 1, n - i, i + 1);

            for mut rr in r.into_iter() {
                rr.push(i);
                result.push(rr);
            }
        }

        result
    }
}

fn main() {
    let k = 3;
    let n = 7;

    let result = Solution::combination_sum3(k, n);

    println!("{:?}", result);
}
