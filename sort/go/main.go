package main

import (
	"fmt"
	"math"
	"math/rand"
	"sort"
	"time"
)

const experiments = 1_000
const capacity = 1_000_000

type TestData struct {
	data []int
}

func testInit() TestData {
	data := make([]int, capacity)
	for i := 0; i < capacity; i++ {
		data[i] = rand.Int()
	}
	return TestData{data}
}

func testRun(test TestData) {
	sort.Ints(test.data)
}

func main() {
	var best int64 = math.MaxInt64
	for k := 0; k < experiments; k++ {
		testData := testInit()
		startAt := time.Now()
		testRun(testData)
		endAt := time.Now()

		current := endAt.Sub(startAt).Nanoseconds()

		if current < best {
			best = current
			fmt.Print("\r", float64(best)/float64(1e6), "ms")
		}
	}
}
