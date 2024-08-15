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
    int32_t* data;
    int32_t target;
};

TestData testInit() {
    TestData test = TestData();
    std::default_random_engine generator;
    std::uniform_int_distribution<int32_t> distribution(0,maxNumber);

    test.data = new int32_t[capacity];
    test.target = 2 * maxNumber + 1;

    for (size_t i = 0; i < capacity; i++) {
        test.data[i] = distribution(generator);
    }
    
    return test;
}

void testRun(const TestData& test) {
    unordered_map<int32_t, bool> seen;

    for (size_t i = 0; i < capacity; i++) {
        int32_t searchFor = test.target - test.data[i];
        if (seen[searchFor]) {
            throw std::runtime_error("This should not happen");
        }

        seen[test.data[i]] = true;
    }
}

void testCleanup(const TestData& test) {
    delete[] test.data;
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

        testCleanup(data);
    }

    return 0;
}