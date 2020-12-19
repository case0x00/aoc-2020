// part 1
// In this game, the players take turns saying numbers. They begin by taking turns reading from a
// list of starting numbers (your puzzle input). Then, each turn consists of considering the most recently spoken number:
// If that was the first time the number has been spoken, the current player says 0.
// Otherwise, the number had been spoken before; the current player announces how many
// turns apart the number is from when it was previously spoken.
// Given your starting numbers, what will be the 2020th number spoken?
// Given your starting numbers, what will be the 30000000th number spoken?

package main

import (
	"fmt"
)

func part1andpart2(input []int, turns int) int {
	memory := make(map[int]int)
	previous := 0
	current := 0

	for i := 1; i <= turns; i++ {
		if i <= len(input) {
			current = input[i-1]
		} else {
			spoken, ok := memory[previous]
			if ok {
				current = i-1-spoken
			} else {
				current = 0
			}
		}
		if i > 1 {
			memory[previous] = i-1
		}
		previous = current
	}
	return previous

}

// not loading data from file since its so short
func main() {
//	var input_test = []int{0,3,6}
	var input = []int{14,8,16,0,1,17}

	fmt.Println(part1andpart2(input, 2020))
	fmt.Println(part1andpart2(input, 30000000))
}