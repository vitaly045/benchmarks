package main

import (
	"fmt"
	"time"
)

func testMap(capacity int) {
	for k := 0; k < 100; k++ {
		a := make(map[int]int, capacity)
		startAt := time.Now()

		for i := 0; i < capacity; i++ {
			a[i] = i * 2
		}

		endAt := time.Now()

		fmt.Println(endAt.Sub(startAt))
	}
}

func main() {
	testMap(1000000)
}
