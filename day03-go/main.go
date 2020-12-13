// part 1

// start by counting all the trees you would 
// encounter for the slope right 3, down 1:
// Starting at the top-left corner of your map
// and following a slope of right 3 and down 1,
// how many trees would you encounter?

// part 2

// Determine the number of trees you would encounter
// if, for each of the following slopes, you start at
// the top-left corner and traverse the map all the way
// to the bottom:
// Right 1, down 1.
// Right 3, down 1. (This is the slope you already checked.)
// Right 5, down 1.
// Right 7, down 1.
// Right 1, down 2.
// What do you get if you multiply together the number of
// trees encountered on each of the listed slopes?

package main

import (
	"strings"
	"io/ioutil"
	"fmt"
)

func TreeCount(terrain []string, x int, y int) int {
	tree := "#"
	count := 0
	x_pos := 0
	y_pos := 0

	// end condition
	for y_pos < len(terrain) {
		slope := terrain[y_pos]
		if slope == "" { break }
		if string(slope[x_pos%len(slope)]) == tree {
			count++
		}
		x_pos += x
		y_pos += y
	}
	return count

}

func main() {
	// grab input text file
	input, _ := ioutil.ReadFile("input.txt")
	// split
	terrain := strings.Split(string(input), "\n")

	// part 1
	fmt.Println("part 1: ", TreeCount(terrain, 3, 1))

	// part 2
	ans := TreeCount(terrain, 1, 1) * 
		   TreeCount(terrain, 3, 1) *
		   TreeCount(terrain, 5, 1) *
		   TreeCount(terrain, 7, 1) *
		   TreeCount(terrain, 1, 2)
	fmt.Println("part 2: ", ans)
}