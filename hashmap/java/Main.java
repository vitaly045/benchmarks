package hashmap.java;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Main {
    private static final int experiments = 5000;
    private static final int capacity = 1000000;
    private static final int maxNumber = 100000;

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

    private static void testRun(TestData test) {
        Map<Integer, Boolean> seen = new HashMap<>();

        for (int i = 0; i < test.data.length; i++) {
            int searchFor = test.target - test.data[i];
            if (seen.containsKey(searchFor)) {
                throw new RuntimeException("This should not happen");
            }

            seen.put(test.data[i], true);
        }
    }

    public static void main(String[] args) {
        double average = 0.0;

        for (int i = 0; i < experiments; i++) {
            TestData data = testInit();
            long start = System.currentTimeMillis();
            testRun(data);
            long end = System.currentTimeMillis();

            average += (double)(end - start) / experiments;
        }

        System.out.println("[Java] Average time: " + average);
    }
}