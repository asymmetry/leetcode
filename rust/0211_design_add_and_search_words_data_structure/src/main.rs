struct WordDictionary {
    pub children: Vec<Option<Box<WordDictionary>>>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl WordDictionary {
    fn new() -> Self {
        let mut children = Vec::with_capacity(27);
        for _ in 0..27 {
            children.push(None);
        }
        Self { children }
    }

    fn add_word(&mut self, word: String) {
        if !word.is_empty() {
            let index = word.chars().nth(0).unwrap() as usize - 'a' as usize;

            if let Some(child) = &mut self.children[index] {
                child.add_word(word[1..].to_string());
            } else {
                let mut new_child = WordDictionary::new();
                new_child.add_word(word[1..].to_string());
                self.children[index] = Some(Box::new(new_child));
            }
        } else {
            if self.children[26].is_none() {
                self.children[26] = Some(Box::new(WordDictionary::new()));
            }
        }
    }

    fn search(&self, word: String) -> bool {
        if !word.is_empty() {
            let ch = word.chars().nth(0).unwrap();

            if ch == '.' {
                for child in self.children.iter().flatten() {
                    if child.search(word[1..].to_string()) {
                        return true;
                    }
                }
                false
            } else {
                let index = ch as usize - 'a' as usize;

                if let Some(child) = &self.children[index] {
                    child.search(word[1..].to_string())
                } else {
                    false
                }
            }
        } else {
            self.children[26].is_some()
        }
    }
}

fn main() {
    let mut obj = WordDictionary::new();
    obj.add_word("bad".to_string());
    obj.add_word("dad".to_string());
    obj.add_word("mad".to_string());
    let ret = obj.search("pad".to_string());
    println!("{}", ret);
    let ret = obj.search("bad".to_string());
    println!("{}", ret);
    let ret = obj.search(".ad".to_string());
    println!("{}", ret);
    let ret = obj.search("b..".to_string());
    println!("{}", ret);
}
