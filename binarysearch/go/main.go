package main

import (
	"fmt"
	"math"
	"math/rand"
	"slices"
	"sort"
	"strconv"
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
	sort.Ints(data)
	return TestData{data}
}

func testRun(test *TestData) {
	for i := 0; i < capacity; i++ {
		_, contains := slices.BinarySearch(test.data, test.data[i])
		if !contains {
			panic("Value is not found: " + strconv.Itoa(test.data[i]))
		}
	}
}

func main() {
	var best int64 = math.MaxInt64

	for k := 0; k < experiments; k++ {
		testData := testInit()
		startAt := time.Now()
		testRun(&testData)
		endAt := time.Now()

		current := endAt.Sub(startAt).Nanoseconds()

		if current < best {
			best = current
			fmt.Println(float64(best)/float64(1e6), "ms")
		}
	}
}
