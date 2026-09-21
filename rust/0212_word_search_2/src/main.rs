struct Trie {
    pub children: Vec<Option<Box<Trie>>>,
}

impl Trie {
    fn new() -> Self {
        let mut children = Vec::new();
        for _ in 0..27 {
            children.push(None);
        }
        Self { children }
    }

    fn insert(&mut self, word: &str) {
        if !word.is_empty() {
            let index = word.chars().nth(0).unwrap() as usize - 'a' as usize;

            if let Some(child) = self.children[index].as_deref_mut() {
                child.insert(&word[1..]);
            } else {
                let mut new_child = Box::new(Trie::new());
                new_child.insert(&word[1..]);
                self.children[index] = Some(new_child);
            }
        } else {
            if self.children[26].is_none() {
                self.children[26] = Some(Box::new(Trie::new()));
            }
        }
    }

    fn search(&self, word: &str) -> bool {
        if !word.is_empty() {
            let index = word.chars().nth(0).unwrap() as usize - 'a' as usize;

            if let Some(child) = self.children[index].as_deref() {
                child.search(&word[1..])
            } else {
                false
            }
        } else {
            self.children[26].is_some()
        }
    }

    fn starts_with(&self, prefix: &str) -> bool {
        if !prefix.is_empty() {
            let index = prefix.chars().nth(0).unwrap() as usize - 'a' as usize;

            if let Some(child) = self.children[index].as_deref() {
                child.starts_with(&prefix[1..])
            } else {
                false
            }
        } else {
            true
        }
    }
}

struct Solution;

impl Solution {
    pub fn find_words(board: Vec<Vec<char>>, words: Vec<String>) -> Vec<String> {
        let m: usize = board.len();
        let n: usize = board[0].len();

        let mut used = Vec::<Vec<bool>>::with_capacity(m);
        for _ in 0..m {
            used.push(vec![false; n]);
        }

        let mut trie = Trie::new();
        for word in words.iter() {
            trie.insert(word);
        }

        let mut result = Vec::<String>::new();

        for i in 0..m {
            for j in 0..n {
                used[i][j] = true;
                Self::search(
                    &board,
                    &mut used,
                    i,
                    j,
                    board[i][j].to_string(),
                    &trie,
                    &mut result,
                );
                used[i][j] = false;
            }
        }

        result
    }

    fn search(
        board: &Vec<Vec<char>>,
        used: &mut Vec<Vec<bool>>,
        row: usize,
        col: usize,
        prefix: String,
        words: &Trie,
        result: &mut Vec<String>,
    ) {
        if !words.starts_with(&prefix) {
            return;
        }

        if words.search(&prefix) && !result.contains(&prefix) {
            result.push(prefix.clone());
        }

        let m = board.len() as isize;
        let n = board[0].len() as isize;

        const DIRS: [[isize; 2]; 4] = [[1, 0], [-1, 0], [0, 1], [0, -1]];

        for dir in DIRS {
            let i = row as isize + dir[0];
            let j = col as isize + dir[1];

            if i < 0 || i >= m || j < 0 || j >= n || used[i as usize][j as usize] {
                continue;
            }

            let i = i as usize;
            let j = j as usize;

            let mut new_prefix = prefix.clone();
            new_prefix.push(board[i][j]);

            used[i][j] = true;
            Self::search(board, used, i, j, new_prefix, words, result);
            used[i][j] = false;
        }
    }
}

fn main() {
    let board = vec![
        vec!['o', 'a', 'a', 'n'],
        vec!['e', 't', 'a', 'e'],
        vec!['i', 'h', 'k', 'r'],
        vec!['i', 'f', 'l', 'v'],
    ];

    let words = vec![
        "oath".to_string(),
        "pea".to_string(),
        "eat".to_string(),
        "rain".to_string(),
    ];
    let result = Solution::find_words(board, words);

    println!("{:?}", result);
}
