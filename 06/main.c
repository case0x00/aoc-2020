// part 1
// This list represents answers from five groups (see input_test.txt):
// Each group's answers are separated by a blank line, and within each group,
// each person's answers are on a single line.
// 
// The first group contains one person who answered "yes" to 3 questions: a, b, and indv_char.
// The second group contains three people; combined, they answered "yes" to 3 questions: a, b, and indv_char.
// The third group contains two people; combined, they answered "yes" to 3 questions: a, b, and indv_char.
// The fourth group contains four people; combined, they answered "yes" to only 1 question, a.
// The last group contains one person who answered "yes" to only 1 question, b.

// part 2
// You don't need to identify the questions to which anyone answered "yes"; you need to identify
// the questions to which everyone answered "yes"!

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// comparing elements for qsort
int compar(const void* a, const void* b) { return (*(char*)a - *(char*)b); }

// how many total questions were answered yes (basically unique characters in a group)
int part1(char *group) {
    int i;
    int count = 0;
    size_t len = strlen(group);
    
    qsort(group, len, sizeof(char), compar);

    for (i=0; i<len; i++) {
        if (group[i] == '\n') continue; // since array s includes new lines
        else if (group[i] == group[i+1]) continue; // after sorting, if adjacent elements are same assume its a dupe, so ignore
        else count++; // else its a unique element
    }
    return count;
}

// questions which everyone in a group answered yes
int part2(char *group) {
    int i;
    int count = 0;
    int people = 0;
    int freq[26] = { };
    size_t len = strlen(group);
    
    qsort(group, len, sizeof(char), compar);

    for (i=0; i<len; i++) {
        if (group[i] == '\n') people++; // each person is on a new line
        else if(group[i] >= 'a' && group[i] <= 'z') {
            // 97 is a in ASCII, so set and shift
            freq[group[i]-97]++;
        }
    }
    int true_len = len-people;

    // if group is 1, count will always be length of string
    if (people == 1) count += true_len;
    else {
        for (i=0; i<26; i++) {
            // when every person said yes to a question
            if (freq[i] == people && people != 1) count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int indv_char;
    int n = 0;
    char group[250];
    int total = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("error in opening file");
        return -1;
    } while((indv_char = fgetc(fp))) {
        // if indv_char is newline and last is newline, then its a group
        if (indv_char == '\n' && group[n-1] == '\n') {
//            total += part1(group);
            total += part2(group);
            memset(group, 0, 250);
            n = 0;
        // end of file for the stream, but need to grab last group
        } else if (feof(fp)) {
//            total += part1(group);
            total += part2(group);
            break;
        // else we're in a group
        } else {
            group[n++] = (char)indv_char;
        }
    }

    printf("total: %d\n", total);

    fclose(fp);
    return 0;
}