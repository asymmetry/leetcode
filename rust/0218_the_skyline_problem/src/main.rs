struct Solution;

impl Solution {
    pub fn get_skyline(buildings: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        use std::collections::{BTreeMap, btree_map};

        let mut skyline = BTreeMap::<i32, i32>::new();

        for b in buildings.iter() {
            let l = b[0];
            let r = b[1];
            let h = b[2];

            let mut vl = 0;
            let mut vr = 0;
            for (k, v) in skyline.iter() {
                if *k <= l {
                    vl = *v;
                }
                if *k <= r {
                    vr = *v;
                }
            }

            vl = vl.max(h);

            match skyline.entry(l) {
                btree_map::Entry::Occupied(entry) => {
                    let entry = entry.into_mut();
                    if *entry < vl {
                        *entry = vl;
                    }
                }
                btree_map::Entry::Vacant(entry) => {
                    entry.insert(vl);
                }
            }

            skyline.entry(r).or_insert(vr);

            for (_, v) in skyline.range_mut(l..r) {
                *v = (*v).max(h);
            }
        }

        let mut result = Vec::<Vec<i32>>::new();

        let mut last = -1;

        for (k, v) in skyline.into_iter() {
            if v != last {
                result.push(vec![k, v]);
            }
            last = v;
        }

        result
    }
}

fn main() {
    let buildings = vec![
        vec![2, 9, 10],
        vec![3, 7, 15],
        vec![5, 12, 12],
        vec![15, 20, 10],
        vec![19, 24, 8],
    ];

    let result = Solution::get_skyline(buildings);

    println!("{:?}", result);
}
