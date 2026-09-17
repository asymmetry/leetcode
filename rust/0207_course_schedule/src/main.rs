struct Solution;

impl Solution {
    pub fn can_finish(num_courses: i32, prerequisites: Vec<Vec<i32>>) -> bool {
        let mut prerequisites_map = vec![Vec::<usize>::new(); num_courses as usize];

        for p in prerequisites {
            prerequisites_map[p[0] as usize].push(p[1] as usize);
        }

        let mut testing = Vec::<(usize, usize)>::new();

        for test in 0..num_courses as usize {
            let mut status = vec![0; num_courses as usize];
            testing.clear();
            testing.push((test, 0));

            while let Some((c, next_id)) = testing.pop() {
                if next_id >= prerequisites_map[c].len() {
                    status[c] = 2;
                    continue;
                }

                testing.push((c, next_id + 1));

                let next_c = prerequisites_map[c][next_id];

                if status[next_c] == 0 {
                    status[next_c] = 1;
                    testing.push((next_c, 0));
                } else if status[next_c] == 1 {
                    return false;
                }
            }
        }

        true
    }
}

fn main() {
    let num_courses = 2;
    let prerequisites = vec![vec![1, 0], vec![0, 1]];

    let result = Solution::can_finish(num_courses, prerequisites);

    println!("{}", result);
}
