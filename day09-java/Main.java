// part 1
// XMAS starts by transmitting a preamble of 25 numbers.
// After that, each number you receive should be the sum
// of any two of the 25 immediately previous numbers.
// The two numbers will have different values, and there
// might be more than one such pair.
// What is the first number that does not have this property?

// part 2
// you must find a contiguous set of at least two numbers in
// your list which sum to the invalid number from part 1.
// To find the encryption weakness, add together the
// smallest and largest number in this contiguous range;

import java.io.*;
import java.util.*;
import java.util.stream.*;
import java.nio.file.*;

public class Main {

//    public static final int PREAMBLE = 5; // input_test
    public static final int PREAMBLE = 25; // input
//    public static final int INVALIDNUM = 127; // input_test
    public static final int INVALIDNUM = 1309761972; // input

    // part 1
    public static long part1(List<Long> lines) {
        // start after preamble
        for (int i = PREAMBLE; i < lines.size(); i++) {
            HashSet<Long> sum = new HashSet<>();
            for (int j = i-PREAMBLE; j < i; j++) {
                for (int k = j; k < i; k++) {
                    sum.add(lines.get(j) + lines.get(k));
                }
            }
            if (!sum.contains(lines.get(i))) {
                return lines.get(i);
            }
        }
        return -1;

    }

    // part 2
    // 177989832
    public static long part2(List<Long> lines) {
        for (int i = 0; i < lines.size(); i++) {
            for (int j = i+1; j < lines.size(); j++) {
                long sum = 0;
                for (int k = i; k < j; k++) {
                    sum += lines.get(k);
                }
                // if its too large just break
                if (sum > INVALIDNUM) {
                    break;
                }
                // found a valid sum
                if (sum == INVALIDNUM) {
                    // arbitrarily large and small values
                    long min = Long.MAX_VALUE;
                    long max = Long.MIN_VALUE;
                    for (int m = i; m < j; m++) {
                        if (min > lines.get(m)) {
                            min = lines.get(m);
                        }
                        if (max < lines.get(m)) {
                            max = lines.get(m);
                        }
                    }
                    return min + max;
                }
            } 
        }
        return -1;
    }

    // main which is executed
    public static void main(String[]args) throws IOException {
        try (Stream<String> stream = Files.lines(Paths.get("input.txt"))) {
            List<Long> lines = stream.map(Long::parseLong).collect(Collectors.toList());
            //System.out.println(part1(lines));
            System.out.println(part2(lines));
            stream.close();
        }

    }
}