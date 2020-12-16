// part 1
// The navigation instructions (your puzzle input) consists of a sequence of
// single-character actions paired with integer input values. After staring at
// them for a few minutes, you work out what they probably mean:
// Action N means to move north by the given value.
// Action S means to move south by the given value.
// Action E means to move east by the given value.
// Action W means to move west by the given value.
// Action L means to turn left the given number of degrees.
// Action R means to turn right the given number of degrees.
// Action F means to move forward by the given value in the direction the ship is currently facing.
// The ship starts by facing east.
// Figure out where the navigation instructions lead. What is the Manhattan distance
// between that location and the ship's starting position?

// part 2
// Action N means to move the waypoint north by the given value.
// Action S means to move the waypoint south by the given value.
// Action E means to move the waypoint east by the given value.
// Action W means to move the waypoint west by the given value.
// Action L means to rotate the waypoint around the ship left (counter-clockwise) the given number of degrees.
// Action R means to rotate the waypoint around the ship right (clockwise) the given number of degrees.
// Action F means to move forward to the waypoint a number of times equal to the given value
// The waypoint starts 10 units east and 1 unit north relative to the ship. The waypoint is relative to the ship;
// that is, if the ship moves, the waypoint moves with it.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum instructions {
    NORTH = 'N',
    SOUTH = 'S',
    EAST = 'E',
    WEST = 'W',
    FORWARD = 'F',
    RIGHT = 'R',
    LEFT = 'L'
};

// part 1
int part1(FILE *fp) {
    char instruction;
    int magnitude;
    int x = 0;
    int y = 0;
    int dir = 1; // 0-3
    char compass[4] = {NORTH, EAST, SOUTH, WEST};

    // read each line and format into instruction and magnitude
    while (fscanf(fp, "%c%d\n", &instruction, &magnitude) > 0) {
//        printf("instruction: %c\n", instruction);
//        printf("magnitude: %d\n", magnitude);

        // FORWARD is most important since it sets direction
        if (instruction == FORWARD) {
            instruction = compass[dir];
        }

        switch(instruction) {
            case NORTH:
                y -= magnitude;
                break;
            case SOUTH:
                y += magnitude;
                break;
            case EAST:
                x += magnitude;
                break;
            case WEST:
                x -= magnitude;
                break;
            case LEFT:
                dir = (dir + 4 - magnitude / 90) % 4;
                break;
            case RIGHT:
                dir = (dir + magnitude / 90) % 4;
                break;
        }
    }
    return abs(x)+abs(y);
}

// part 2
int part2(FILE *fp) {
    char instruction;
    int magnitude;
    int x = 0;
    int y = 0;
    int dir = 1; // 0-3
    char compass[4] = {NORTH, EAST, SOUTH, WEST};
    int wx = 10; // east waypoint coord
    int wy = -1; // north waypoint coord
    int turn, tmp, i;

    while (fscanf(fp, "%c%d\n", &instruction, &magnitude) > 0) {

        switch(instruction) {
            case FORWARD:
                x += wx * magnitude;
                y += wy * magnitude;
                break;
            case NORTH:
                wy -= magnitude;
                break;
            case SOUTH:
                wy += magnitude;
                break;
            case EAST:
                wx += magnitude;
                break;
            case WEST:
                wx -= magnitude;
                break;
            case LEFT:
                i = 0;
                turn = magnitude/90;
                while (i++ < turn) {
                    tmp = wx;
                    wx = wy;
                    wy = -tmp;
                }
                break;
            case RIGHT:
                i = 0;
                turn = magnitude/90;
                while (i++ < turn) {
                    tmp = wx;
                    wx = -wy;
                    wy = tmp;
                }
                break;
        }
    }
    return abs(x)+abs(y);
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char ch;

    fp = fopen("input.txt", "r");
    
    if (fp == NULL) {
        perror("error in opening file");
        return -1;
    }

    // part 1
//    printf("part 1: %d\n", part1(fp));
    // part 2
    printf("part 2: %d\n", part2(fp));

    fclose(fp);
    return 0;
}