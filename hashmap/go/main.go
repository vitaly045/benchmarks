package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

const experiments = 1_000
const capacity = 1_000_000
const maxNumber = 10_000_000

type TestData struct {
	data   []int
	target int
}

func testInit() TestData {
	data := make([]int, capacity)
	for i := 0; i < capacity; i++ {
		data[i] = rand.Intn(maxNumber)
	}
	return TestData{data, 2*maxNumber + 1}
}

func testRun(test TestData) int {
	seen := map[int]bool{}
	length := len(test.data)
	for i := 0; i < length; i++ {
		searchFor := test.target - test.data[i]
		if _, contains := seen[searchFor]; contains {
			panic("Found two numbers which add up to a target")
		}
		seen[test.data[i]] = true
	}

	return len(seen)
}

func main() {
	var best int64 = math.MaxInt64
	for k := 0; k < experiments; k++ {
		testData := testInit()
		startAt := time.Now()
		countDistinct := testRun(testData)
		endAt := time.Now()

		current := endAt.Sub(startAt).Nanoseconds()

		if current < best {
			best = current
			fmt.Println(float64(best)/float64(1e6), "ms", "distinct = ", countDistinct)
		}
	}
}
