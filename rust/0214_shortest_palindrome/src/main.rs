struct Solution;

impl Solution {
    pub fn shortest_palindrome(s: String) -> String {
        let len = s.len();

        if s.is_empty() {
            return "".to_string();
        }

        if len == 1 {
            return s;
        }

        let cs = s.chars().collect::<Vec<_>>();
        let mut pl = 0;

        for l in (1..=len).rev() {
            let mut test = 0;
            while test < l - 1 - test && cs[test] == cs[l - 1 - test] {
                test += 1;
            }
            if cs[test] == cs[l - 1 - test] {
                pl = l;
                break;
            }
        }

        let mut result = s.clone();
        for c in cs.iter().skip(pl) {
            result = c.to_string() + &result;
        }

        result
    }
}

fn main() {
    let s = "aacecaaa";

    let result = Solution::shortest_palindrome(s.to_string());

    println!("{}", result);
}
