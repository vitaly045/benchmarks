using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace main {
    struct TestData {
        public int[] data;
        public int target;
    }

    class Program {
        static int capacity = 1_000_000;
        static int maxNumber = 100_000;
        static int experiments = 1000;

        static TestData testInit() {
            var rand = new Random();
            var test = new TestData();
            test.data = new int[capacity];
            test.target = 2 * maxNumber + 1;

            for (int i = 0; i < capacity; i++) {
                test.data[i] = rand.Next(maxNumber);
            }

            return test;
        }

        static void testRun(TestData test) {
            Dictionary<int, bool> seen = new Dictionary<int, bool>();

            for (int i = 0; i < test.data.Length; i++) {
                int searchFor = test.target - test.data[i];

                if (seen.ContainsKey(searchFor)) {
                    throw new Exception("This should not happen");
                }

                seen[test.data[i]] = true;
            }
        }

        static void RunExperiments() {
            double average = 0.0;

            for (int i = 0; i < experiments; i++) {
                TestData testData = testInit();

                var watch = Stopwatch.StartNew();
                testRun(testData);
                watch.Stop();

                average += ((double)watch.ElapsedMilliseconds) / experiments;
            }

            Console.WriteLine("[C#] Average time: " + average);
        }

        public static void Main() {
            RunExperiments();
        }
    }
}