package bitset.java;

import java.util.BitSet;
import java.util.Random;

public class Main {
    private static final int experiments = 1000;
    private static final int capacity = 1000000;
    private static final int maxNumber = 10000000;

    static class TestData {
        int[] data;
        int target;
    }

    private static TestData testInit() {
        TestData test = new TestData();
        Random rand = new Random();

        test.data = new int[capacity];
        test.target = 2 * maxNumber + 1;

        for (int i = 0; i < capacity; i++) {
            test.data[i] = rand.nextInt(maxNumber);
        }

        return test;
    }

    private static int testRun(TestData test) {
        BitSet seen = new BitSet();

        for (int i = 0; i < test.data.length; i++) {
            int searchFor = test.target - test.data[i];
            if (seen.get(searchFor)) {
                throw new RuntimeException("Found 2 numbers which add up to a target");
            }

            seen.set(test.data[i]);
        }

        return seen.cardinality();
    }

    public static void main(String[] args) {
        double best = Double.MAX_VALUE;

        for (int i = 0; i < experiments; i++) {
            TestData data = testInit();
            long start = System.nanoTime();
            int countDistinct = testRun(data);
            long end = System.nanoTime();

            double current = (double)(end - start) / 1E6;
            if (current < best) {
                best = current;
                System.out.println(best + "ms" + ", distinct = " + countDistinct);
            }
        }
    }
}
