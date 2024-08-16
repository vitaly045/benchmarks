#include <chrono>
#include <iostream>
#include <random>
#include <climits>
#include <unordered_map>
#include <functional>

using namespace std;

const int experiments = 1000;
const int capacity = 1000000;
const int maxNumber = 1000000;

struct TestData {
    vector<int> data;
    int target;
};

TestData testInit() {
    TestData test = TestData();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,maxNumber);

    test.target = 2 * maxNumber + 1;

    for (size_t i = 0; i < capacity; i++) {
        test.data.push_back(distribution(generator));
    }
    
    return test;
}

void testRun(const TestData& test) {
    unordered_map<int, bool> seen;

    for (size_t i = 0; i < capacity; i++) {
        int searchFor = test.target - test.data[i];
        if (seen.find(searchFor) != seen.end()) {
            throw std::runtime_error("Found two numbers add up to a target");
        }

        seen[test.data[i]] = true;
    }
}

int main() {
    double best = INT64_MAX;

    for (size_t i = 0; i < experiments; i++) {
        TestData data = testInit();
        auto start_time = chrono::high_resolution_clock::now();
        testRun(data);
        auto end_time = chrono::high_resolution_clock::now();
        auto time = (end_time - start_time) / chrono::nanoseconds(1);

        if (time < best) {
            best = time;
            cout << "\r" << best / 1e6 << "ms";
        }
    }

    return 0;
}