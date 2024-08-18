#include <chrono>
#include <iostream>
#include <random>
#include <climits>
#include <unordered_set>

const int experiments = 1000;
const int capacity = 1000000;
const int maxNumber = 10000000;

struct TestData {
    int* data;
    int target;
};

TestData testInit() {
    TestData test = TestData();
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0,maxNumber);

    test.target = 2 * maxNumber + 1;
    test.data = new int[capacity];

    for (size_t i = 0; i < capacity; i++) {
        test.data[i] = distribution(generator);
    }

    return test;
}

int testRun(const TestData& test) {
    std::unordered_set<int> seen;

    for (size_t i = 0; i < capacity; i++) {
        int searchFor = test.target - test.data[i];
        if (seen.find(searchFor) != seen.end()) {
            throw std::runtime_error("Found two numbers add up to a target");
        }

        seen.insert(test.data[i]);
    }

    return seen.size();
}

void testCleanup(const TestData& test) {
    delete[] test.data;
}

int main() {
    double best = INT64_MAX;

    for (size_t i = 0; i < experiments; i++) {
        TestData test = testInit();

        auto start_time = std::chrono::high_resolution_clock::now();
        auto count_distinct = testRun(test);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto current = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

        if (current < best) {
            best = current;
            std::cout << best / 1e6 << "ms" << ", distinct = " << count_distinct << std::endl;
        }

        testCleanup(test);
    }

    return 0;
}