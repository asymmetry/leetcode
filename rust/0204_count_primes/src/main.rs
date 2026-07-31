struct Solution;

impl Solution {
    pub fn count_primes(n: i32) -> i32 {
        if n < 3 {
            return 0;
        }

        let mut is_prime = vec![true; n as usize];
        is_prime[0] = false;
        is_prime[1] = false;

        let test_n = n.isqrt();

        for i in 2..=test_n {
            if !is_prime[i as usize] {
                continue;
            }

            for j in ((i * i)..n).step_by(i as usize) {
                is_prime[j as usize] = false;
            }
        }

        is_prime.iter().filter(|x| **x).count() as i32
    }
}

fn main() {
    let n = 10;

    let result = Solution::count_primes(n);

    println!("{}", result);
}
