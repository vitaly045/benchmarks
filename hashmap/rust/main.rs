use std::collections::HashSet;
use rand::Rng;
use std::time::Instant;

const CAPACITY:usize = 1_000_000;
const MAX_NUMBER:i32 = 10_000_000;
const EXPERIMENTS:usize = 1000;

struct TestData {
    data: Vec<i32>,
    target: i32
}

fn test_init() -> TestData {
    let mut rng = rand::thread_rng();
    let mut data = Vec::with_capacity(CAPACITY);
    for _i in 0..CAPACITY {
        data.push(rng.gen_range(0..MAX_NUMBER));
    }
    TestData{ data: data, target: 2*MAX_NUMBER + 1}
}

fn test_run(test: &TestData) -> usize {
    let mut seen = HashSet::new();
    
    for num in &test.data {
        let search_for = test.target - num;

        if seen.contains(&search_for) {
            panic!("Found two numbers which add up to a target");
        }

        seen.insert(num);
    }

    seen.len()
}

fn main() {
    let mut best = std::u128::MAX;

    for _i in 0..EXPERIMENTS {
        let test = test_init();
        let start = Instant::now();
        let distinct = test_run(&test);
        let current = start.elapsed().as_nanos();

        if current < best {
            best = current;
            println!("{:?}ms, distinct = {:?}", (best as f64) / 1000000.0, distinct);
        }
    }
}