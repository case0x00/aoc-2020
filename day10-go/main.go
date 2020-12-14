// part 1
// device -> adapter -> outlet
// Any given adapter can take an input 1, 2, or 3 jolts lower
// than its rating (puzzle input) and still produce its rated output joltage.
// In addition, your device has a built-in joltage adapter rated for 3 jolts
// higher than the highest-rated adapter in your bag.
// Treat the charging outlet near your seat as having an effective joltage rating of 0.
// If you use every adapter in your bag at once, what is the distribution of joltage
// differences between the charging outlet, the adapters, and your device?
// Find a chain that uses all of your adapters to connect the charging outlet
// to your device's built-in adapter and count the joltage differences between the
// charging outlet, the adapters, and your device. What is the number of 1-jolt differences
// multiplied by the number of 3-jolt differences?

// part 2
// To completely determine whether you have enough adapters, you'll need to figure out how many
// different ways they can be arranged. Every arrangement needs to connect the charging outlet
// to your device. The previous rules about when adapters can successfully connect still apply.
// What is the total number of distinct ways you can arrange the adapters to connect the charging
// outlet to your device?


package main

import (
	"bufio"
	"strconv"
	"os"
	"fmt"
	"sort"
)

// part 1
func part1(adapters []int) int {

	sort.Ints(adapters)
	var chain [3]int
	chain[0] = 1
	chain[2] = 1

	for i := 0; i < len(adapters)-1; i++ {
		switch c := adapters[i+1] - adapters[i]; c {
		case 3:
			chain[2]++
		case 1:
			chain[0]++

		}
	}
	return chain[2] * chain[0]
}

// part 2
func part2(adapters []int) uint64 {

	sort.Ints(adapters)
	adapters = append([]int{0}, append(adapters, adapters[len(adapters)-1]+3)...)

	m := map[int]uint64{}
	var next func(int) uint64

	next = func(idx int) uint64 {
		if m[idx] != 0 {
			return m[idx]
		}
		if idx == len(adapters)-1 {
			return 1
		}
		var sum uint64
		for i := idx + 1; i < len(adapters); i++ {
			if adapters[i]-adapters[idx] > 3 {
				break
			}
			n := next(i)
			sum += n
			m[i] = n
		}
		return sum
	}
	return next(0)
}


// idk why go has such a hard time reading files unlike other langs
func read_file(name string) []int {
	var ret []int
	f, _ := os.Open(name)
	defer f.Close()
	scanner := bufio.NewScanner(f)	
	for scanner.Scan() {
		n, _ := strconv.Atoi(scanner.Text())
		ret = append(ret, n)
	}
	return ret
}

func main() {
	in := read_file("input.txt")
//	fmt.Println(part1(in))
	fmt.Println(part2(in))
}