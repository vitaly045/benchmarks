import time
import random

experiments = 1000
capacity = 1000000

class TestData:
    def __init__(self):
        self.data = []

def test_init():
    test = TestData()
    test.data = [random.randint(-2^63, 2^63 - 1) for _ in range(capacity)]
    return test

def test_run(test):
    sorted(test.data)

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
