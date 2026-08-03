use std::collections::{HashMap, HashSet, hash_map};

struct Solution;

impl Solution {
    pub fn is_isomorphic(s: String, t: String) -> bool {
        if s.len() != t.len() {
            return false;
        }

        let mut map = HashMap::<char, char>::default();
        let mut set = HashSet::<char>::default();

        for (cs, ct) in s.chars().zip(t.chars()) {
            if let hash_map::Entry::Vacant(e) = map.entry(cs) {
                if set.contains(&ct) {
                    return false;
                }
                e.insert(ct);
                set.insert(ct);
            } else {
                if map[&cs] != ct {
                    return false;
                }
            }
        }

        true
    }
}

fn main() {
    let s = "badc".to_string();
    let t = "baba".to_string();

    let result = Solution::is_isomorphic(s, t);

    println!("{}", result);
}
