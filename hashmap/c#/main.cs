using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace main {
    struct TestData {
        public int[] data;
        public int target;
    }

    class Program {
        static readonly int capacity = 1_000_000;
        static readonly int maxNumber = 10_000_000;
        static readonly int experiments = 1000;

        static TestData TestInit() {
            var rand = new Random();
            var test = new TestData {
                data = new int[capacity],
                target = 2 * maxNumber + 1
            };

            for (int i = 0; i < capacity; i++) {
                test.data[i] = rand.Next(maxNumber);
            }

            return test;
        }

        static int TestRun(TestData test) {
            HashSet<int> seen = [];

            for (int i = 0; i < test.data.Length; i++) {
                int searchFor = test.target - test.data[i];

                if (seen.Contains(searchFor)) {
                    throw new Exception("Found two numbers add up to a target value");
                }

                seen.Add(test.data[i]);
            }

            return seen.Count;
        }

        public static void Main() {
            TimeSpan best = TimeSpan.MaxValue;

            for (int i = 0; i < experiments; i++) {
                TestData testData = TestInit();

                var watch = Stopwatch.StartNew();
                var countDistict = TestRun(testData);
                watch.Stop();

                if (watch.Elapsed.CompareTo(best) < 0) {
                    best = watch.Elapsed;
                    Console.WriteLine((best.TotalMicroseconds / 1000.0).ToString("0.00") + "ms" + ", distinct = " + countDistict);
                }
            }
        }
    }
}