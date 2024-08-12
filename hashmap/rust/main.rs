use std::collections::HashMap;
use rand::Rng;
use std::time::Instant;

const CAPACITY:usize = 1_000_000;
const MAX_NUMBER:i32 = 100_000;
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

fn test_run(test: &TestData) {
    let mut map = HashMap::new();
    
    for num in &test.data {
        let search_for = test.target - num;

        if map.contains_key(&search_for) {
            panic!("Found 2 numbers which add up to a target");
        }
        
        map.insert(num, true);
    }
}

fn main() {
    let mut average = 0.0;

    for _i in 0..EXPERIMENTS {
        let test = test_init();
        let start = Instant::now();
        test_run(&test);
        let duration = start.elapsed();

        average += (duration.as_millis() as f64) / (EXPERIMENTS as f64); 
    }

    println!("[Rust] Average time: {:?}", average);
}