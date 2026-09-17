struct Trie {
    pub children: Vec<Option<Box<Trie>>>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl Trie {
    fn new() -> Self {
        let mut children = Vec::new();
        for _ in 0..27 {
            children.push(None);
        }
        Self { children }
    }

    fn insert(&mut self, word: String) {
        if !word.is_empty() {
            let index = word.chars().nth(0).unwrap() as usize - 'a' as usize;

            if let Some(child) = self.children[index].as_deref_mut() {
                child.insert(word[1..].to_string());
            } else {
                let mut new_child = Box::new(Trie::new());
                new_child.insert(word[1..].to_string());
                self.children[index] = Some(new_child);
            }
        } else {
            if self.children[26].is_none() {
                self.children[26] = Some(Box::new(Trie::new()));
            }
        }
    }

    fn search(&self, word: String) -> bool {
        if !word.is_empty() {
            let index = word.chars().nth(0).unwrap() as usize - 'a' as usize;

            if let Some(child) = self.children[index].as_deref() {
                child.search(word[1..].to_string())
            } else {
                false
            }
        } else {
            self.children[26].is_some()
        }
    }

    fn starts_with(&self, prefix: String) -> bool {
        if !prefix.is_empty() {
            let index = prefix.chars().nth(0).unwrap() as usize - 'a' as usize;

            if let Some(child) = self.children[index].as_deref() {
                child.starts_with(prefix[1..].to_string())
            } else {
                false
            }
        } else {
            true
        }
    }
}

fn main() {
    let mut obj = Trie::new();
    obj.insert("apple".to_string());
    let ret = obj.search("apple".to_string());
    println!("{}", ret);
    let ret = obj.search("app".to_string());
    println!("{}", ret);
    let ret = obj.starts_with("app".to_string());
    println!("{}", ret);
    obj.insert("app".to_string());
    let ret = obj.search("app".to_string());
    println!("{}", ret);
}
