struct Solution;

impl Solution {
    pub fn is_happy(n: i32) -> bool {
        let mut used = vec![false; 810];

        let mut n = n;
        while n != 1 {
            let mut next_n = 0;
            while n > 0 {
                let res = n % 10;
                next_n += res.pow(2);
                n /= 10;
            }

            n = next_n;

            if used[n as usize] && n != 1 {
                return false;
            }

            used[n as usize] = true;
        }

        true
    }
}

fn main() {
    let n = 2;

    let result = Solution::is_happy(n);

    println!("{}", result);
}
