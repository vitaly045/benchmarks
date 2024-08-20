using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace main {
    struct TestData {
        public int[] data;
    }

    class Program {
        static int capacity = 1_000_000;
        static int experiments = 1000;

        static TestData testInit() {
            var rand = new Random();
            var test = new TestData();
            test.data = new int[capacity];

            for (int i = 0; i < capacity; i++) {
                test.data[i] = rand.Next();
            }

            return test;
        }

        static void testRun(TestData test) {
            Array.Sort(test.data);
        }

        public static void Main() {
            TimeSpan best = TimeSpan.MaxValue;

            for (int i = 0; i < experiments; i++) {
                TestData testData = testInit();

                var watch = Stopwatch.StartNew();
                testRun(testData);
                watch.Stop();

                if (watch.Elapsed.CompareTo(best) < 0) {
                    best = watch.Elapsed;
                    Console.WriteLine(best.TotalMicroseconds / 1000.0 + "ms");
                }
            }
        }
    }
}