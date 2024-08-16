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
    seen = {}

    for value in test.data:
        search_for = test.target - value
        if search_for in seen:
            raise RuntimeError("Found 2 numbers which add up to a target")
        
        seen[value] = True

def main():
    best = float('inf')

    for _ in range(experiments):
        data = test_init()
        start = time.time()
        test_run(data)
        end = time.time()

        best = min(best, (end - start) * 1E3)
        print(f"\r{best:.6f}", end="")

if __name__ == "__main__":
    main()
