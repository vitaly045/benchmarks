package main

import (
	"fmt"
	"math/rand"
	"time"
)

const experiments = 1_000
const capacity = 1_000_000
const maxNumber = 100_000

type TestData struct {
	data   []int32
	target int32
}

func testInit() TestData {
	data := make([]int32, capacity)

	for i := 0; i < capacity; i++ {
		data[i] = int32(rand.Intn(maxNumber))
	}

	return TestData{data, 2*maxNumber + 1}
}

func testRun(test TestData) {
	seen := map[int32]bool{}
	length := len(test.data)

	for i := 0; i < length; i++ {
		searchFor := test.target - test.data[i]
		if seen[searchFor] {
			panic("This should not happen")
		}

		seen[test.data[i]] = true
	}
}

func main() {
	average := 0.0

	for k := 0; k < experiments; k++ {
		testData := testInit()
		startAt := time.Now()
		testRun(testData)
		endAt := time.Now()

		ms := endAt.Sub(startAt).Milliseconds()
		average += float64(ms) / float64(experiments)
	}

	fmt.Println("[Go] Average running time:", average, "ms")
}
