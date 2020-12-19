// part 1
// The initialization program (your puzzle input) can either update the bitmask or write a value to memory.
// Values and memory addresses are both 36-bit unsigned integers.
// The bitmask is always given as a string of 36 bits, written with the most significant bit (representing 2^35)
// on the left and the least significant bit (2^0, that is, the 1s bit) on the right. The current bitmask is
// applied to values immediately before they are written to memory: a 0 or 1 overwrites the corresponding bit
// in the value, while an X leaves the bit in the value unchanged.
// To initialize your ferry's docking program, you need the sum of all values left in memory after the
// initialization program completes. (The entire 36-bit address space begins initialized to the value 0 at every address.)
// Execute the initialization program. What is the sum of all values left in memory after it completes?
// (Do not truncate the sum to 36 bits.)

// part2
// A version 2 decoder chip doesn't modify the values being written at all. Instead, it acts as a memory address decoder.
// Immediately before a value is written to memory, each bit in the bitmask modifies the corresponding bit of the destination
// memory address in the following way:
// If the bitmask bit is 0, the corresponding memory address bit is unchanged.
// If the bitmask bit is 1, the corresponding memory address bit is overwritten with 1.
// If the bitmask bit is X, the corresponding memory address bit is floating.
// A floating bit is not connected to anything and instead fluctuates unpredictably. In practice, this means the floating bits
// will take on all possible values, potentially causing many memory addresses to be written all at once!
// Execute the initialization program using an emulator for a version 2 decoder chip. What is the sum of all values
// left in memory after it completes?


use regex::Regex;
use std::collections::HashMap;

// part 1
#[allow(dead_code)]
fn part1(input: &Vec<String>) -> i64 {
    let mut mem: HashMap<i64, i64> = HashMap::new();

    // mask to get unchanged bits
    let mut and_mask: i64 = 0;
    // mask to get bits to add
    let mut or_mask: i64 = 0;
    // bitmask regex
    let mask_regex = Regex::new(r"^mask = ([01X]{36})$").unwrap();
    // memory assignment regex
    let mem_regex = Regex::new(r"^mem\[(\d+)\] = (\d+)$").unwrap();

    input.iter()
         .for_each(|l| {
            // match bitmask
            if let Some(caps) = mask_regex.captures(l) {
                let mask_str = caps.get(1).unwrap().as_str();
                and_mask = i64::from_str_radix(&mask_str.replace('X',"1"), 2).unwrap();
                or_mask = i64::from_str_radix(&mask_str.replace('X',"0"), 2).unwrap();
            // match memory assignment
            } else if let Some(caps) = mem_regex.captures(l) {
                let address = caps.get(1).unwrap().as_str().parse::<i64>().unwrap();
                let val = caps.get(2).unwrap().as_str().parse::<i64>().unwrap();
                // set new value after applying bitmask
                mem.insert(address, val & and_mask | or_mask);
            }

        });
    mem.values().sum()
}

// part 2
#[allow(dead_code)]
fn part2(input: &Vec<String>) -> i64 {
    let mut mem: HashMap<i64, i64> = HashMap::new();

    // mask to get unchanged bits
    let mut and_mask: i64 = 0;
    // mask to get bits to add
    let mut or_mask: i64 = 0;

    let mask_regex = Regex::new(r"^mask = ([01X]{36})$").unwrap();
    let mem_regex = Regex::new(r"^mem\[(\d+)\] = (\d+)$").unwrap();

    input.iter()
         .for_each(|l| {
             if let Some(caps) = mask_regex.captures(l) {
                 let mask_str = caps.get(1).unwrap().as_str();
                 and_mask = i64::from_str_radix(&mask_str.replace('X',"1"), 2).unwrap();
                 or_mask = i64::from_str_radix(&mask_str.replace('X',"0"), 2).unwrap();

             } else if let Some(caps) = mem_regex.captures(l) {
                 let address = caps.get(1).unwrap().as_str().parse::<i64>().unwrap();
                 let val = caps.get(2).unwrap().as_str().parse::<i64>().unwrap();
                 let bit_diff = and_mask ^ or_mask;

                 for num_of_addrs in 0..2i64.pow(bit_diff.count_ones()) {
                     let addr_to_write = (0..bit_diff.count_ones() as i64)
                        .fold(
                            (address | and_mask, bit_diff),
                            |(temp_addr, temp_bit_diff), ones_counter| {
                                (
                                    temp_addr ^ bit_diff & (temp_bit_diff ^ (temp_bit_diff - (num_of_addrs >>ones_counter & 1))),
                                    temp_bit_diff & (temp_bit_diff-1),
                                )
                            },
                        ).0;
                        mem.insert(addr_to_write, val);
                 }
             }
         });
         mem.values().sum()
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let file = std::fs::read_to_string("data/input.txt").unwrap();

    let program: Vec<String>  = file.lines()
                                    .map(|s| s.to_string())
                                    .collect::<Vec<String>>();

    println!("part 1: {}", part1(&program));
    println!("part 2: {}", part2(&program));
    Ok(())
}