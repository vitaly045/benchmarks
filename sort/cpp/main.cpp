#include <chrono>
#include <iostream>
#include <random>
#include <climits>
#include <algorithm>

using namespace std;

const int experiments = 1000;
const int capacity = 1000000;

struct TestData {
    int* data;
};

TestData testInit() {
    TestData test = TestData();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(INT32_MIN,INT32_MAX);

    test.data = new int[capacity];

    for (size_t i = 0; i < capacity; i++) {
        test.data[i] = distribution(generator);
    }
    
    return test;
}

void testRun(TestData& test) {
    sort(test.data, test.data + capacity);
}

void testCleanup(TestData& test) {
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
            cout << best / 1e6 << "ms" << endl;
        }

        testCleanup(data);
    }

    return 0;
}