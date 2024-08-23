use rand::Rng;
use std::time::Instant;

const CAPACITY:usize = 1_000_000;
const EXPERIMENTS:usize = 1000;

struct TestData {
    data: Vec<i32>
}

fn test_init() -> TestData {
    let mut rng = rand::thread_rng();
    let mut data = Vec::with_capacity(CAPACITY);
    for _i in 0..CAPACITY {
        data.push(rng.gen());
    }
    data.sort();
    TestData{ data }
}

fn test_run(test: &TestData) {
    for i in 0..CAPACITY {
        let key = test.data[i];
        let _ = test.data.binary_search(&key);
    }
}

fn main() {
    let mut best = std::u128::MAX;

    for _i in 0..EXPERIMENTS {
        let test = test_init();
        let start = Instant::now();
        test_run(&test);
        let current = start.elapsed().as_nanos();

        if current < best {
            best = current;
            println!("{:?}ms", (best as f64) / 1000000.0);
        }
    }
}