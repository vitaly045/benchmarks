package sort.java;

import java.util.Arrays;
import java.util.Random;

public class Main {
    private static final int experiments = 1000;
    private static final int capacity = 1000000;

    static class TestData {
        int[] data;
    }

    private static TestData testInit() {
        TestData test = new TestData();
        Random rand = new Random();

        test.data = new int[capacity];

        for (int i = 0; i < capacity; i++) {
            test.data[i] = rand.nextInt();
        }

        return test;
    }

    private static void testRun(TestData test) {
        Arrays.sort(test.data);
    }

    public static void main(String[] args) {
        double best = Double.MAX_VALUE;

        for (int i = 0; i < experiments; i++) {
            TestData data = testInit();
            long start = System.nanoTime();
            testRun(data);
            long end = System.nanoTime();
            
            double current = (double)(end - start) / 1E6;
            if (current < best) {
                best = current;
                System.out.println(best + "ms");
            }
        }
    }
}