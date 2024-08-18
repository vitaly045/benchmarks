import time
import random

experiments = 1000
capacity = 1000000
max_number = 1000000

class TestData:
    def __init__(self):
        self.data = []
        self.target = 2 * max_number + 1

def test_init():
    test = TestData()
    test.data = [random.randint(0, max_number - 1) for _ in range(capacity)]
    return test

def test_run(test):
    seen = set()

    for value in test.data:
        search_for = test.target - value
        if search_for in seen:
            raise RuntimeError("Found 2 numbers which add up to a target")
        
        seen.add(value)

def main():
    best = float('inf')

    for _ in range(experiments):
        data = test_init()
        start = time.time()
        test_run(data)
        end = time.time()
        current = (end - start) * 1E3

        if current < best:
            best = current
            print(f"{best:.2f}ms")

if __name__ == "__main__":
    main()
