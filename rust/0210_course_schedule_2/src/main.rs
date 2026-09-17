struct Solution;

impl Solution {
    pub fn find_order(num_courses: i32, prerequisites: Vec<Vec<i32>>) -> Vec<i32> {
        let mut map_f = vec![Vec::<usize>::new(); num_courses as usize]; // a dep on b
        let mut map_r = vec![Vec::<usize>::new(); num_courses as usize]; // a dep by b
        for pre in prerequisites {
            map_f[pre[0] as usize].push(pre[1] as usize);
            map_r[pre[1] as usize].push(pre[0] as usize);
        }

        let mut result = Vec::new();

        let mut status = vec![0; num_courses as usize];
        let mut testing = Vec::<(usize, usize)>::new();

        #[allow(clippy::needless_range_loop)]
        for test in 0..num_courses as usize {
            if !map_r[test].is_empty() {
                // the course is dep by others
                continue;
            }

            testing.clear();
            testing.push((test, 0));

            let mut local_result = Vec::new();

            while let Some((c, next_id)) = testing.pop() {
                if next_id >= map_f[c].len() {
                    status[c] = 2;
                    local_result.push(c as i32);
                    continue;
                }

                testing.push((c, next_id + 1));

                let next_c = map_f[c][next_id];

                if status[next_c] == 0 {
                    testing.push((next_c, 0));
                    status[next_c] = 1;
                } else if status[next_c] == 1 {
                    // cycle detected
                    return Vec::new();
                }
            }

            result.extend(local_result);
        }

        if result.len() == num_courses as usize {
            result
        } else {
            Vec::new()
        }
    }
}

fn main() {
    let num_courses = 4;
    let prerequisites = vec![vec![1, 0], vec![2, 0], vec![3, 1], vec![3, 2]];

    let result = Solution::find_order(num_courses, prerequisites);

    println!("{:?}", result);
}
