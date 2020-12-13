// part 1
// one instruction per line with one op and an arg
// acc is accumulator, increases/decreases single global variable by the arg
// jmp jumps to a new instruction relative to itself as offset by the arg
// nop is no op
// Run your copy of the boot code. Immediately before any instruction is
// executed a second time, what value is in the accumulator?

// part 2
// After some careful analysis, you believe that exactly one instruction is corrupted.
// Somewhere in the program, either a jmp is supposed to be a nop, or a nop is supposed
// to be a jmp. (No acc instructions were harmed in the corruption of this boot code.)
// Fix the program so that it terminates normally by changing exactly one jmp (to nop)
// or nop (to jmp). What is the value of the accumulator after the program terminates?

use std::collections::HashSet;
use std::str::FromStr;
use std::num::ParseIntError;
use itertools::Itertools;

// instructions
#[derive(Debug, Clone)]
enum Instruction {
    Acc { value: i32 }, // acc -> accumulator += val
    Jmp { value: i32 }, // jmp -> continue program by val
    Nop { value: i32 }, // nop -> continues program by 1 (jmp by 1), ignore val
}

// instruction error when implementing FromStr
#[derive(Debug, Clone)]
struct ParseInstructionError;

// state of the program
#[derive(Debug)]
struct Program {
    position: i32, // position in the program
    accumulator: i32, // value of the accumulator
}

// termination conditions
#[derive(Debug)]
enum Termination {
    InfLoop, // infinite loop
    End, // end of program
}

// implementing ParseInstructionError
impl From<ParseIntError> for ParseInstructionError {
    fn from(_: ParseIntError) -> ParseInstructionError {
        ParseInstructionError {}
    }
}

// implementing FromStr for Instruction
impl FromStr for Instruction {
    type Err = ParseInstructionError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (instr, argument) = s.split(" ")
                                .take(2)
                                .collect_tuple::<(_, _)>()
                                .ok_or(ParseInstructionError)?;
        let a = argument.parse::<i32>()?;

        match instr {
            "acc" => Ok(Instruction::Acc { value: a }),
            "jmp" => Ok(Instruction::Jmp { value: a }),
            "nop" => Ok(Instruction::Nop { value: a }),
            _ => Err(ParseInstructionError),
        }
    }
}

// program has instructions, a state, and a termination condition
impl Program {
    fn new() -> Self {
        Self {
            position: 0,
            accumulator: 0,
        }
    }

    fn run(&mut self, program: &Vec<Instruction>) -> (Termination, i32) {
        // to ensure the program resets, set to 0
        self.accumulator = 0;
        self.position = 0;

        let mut visited: HashSet<i32> = HashSet::new();
        loop {
            // if it returns to the same value
            if visited.contains(&self.position) {
                return (Termination::InfLoop, self.accumulator);
            }

            // if it hits end of program
            if self.position == program.len() as i32 {
                return (Termination::End, self.accumulator);
            }

            // if its neither, then continue to run program
            visited.insert(self.position);
            let instruct = &program[self.position as usize];
            // match for the instruction type
            match instruct {
                Instruction::Acc { value: val } => {
                    self.accumulator += val;
                    self.position += 1;
                }
                Instruction::Jmp { value: val } => self.position += val,
                Instruction::Nop { .. } => self.position += 1,
            }
        }
    }
}

// part 1 returns accumulator value after infinite loop is detected
#[allow(dead_code)]
fn part1(instructions: &Vec<Instruction>) -> i32 {
    let mut p = Program::new();
    let (_, accumulator) = p.run(instructions);
    return accumulator;
}

// part 2 returns accumulator value after program termination is detected
// which is defined by n+1th instruction executing in a n-length program
// loop through the program, changing jmp -> acc or acc -> jmp until End
#[allow(dead_code)]
fn part2(instructions: &Vec<Instruction>) -> i32 {
    let mut p = Program::new();

    (0..instructions.len())
                    .find_map(|i| {
                        let mut instructions = instructions.clone();
                        instructions[i] = match instructions[i] {
                            Instruction::Jmp { value: x } => Instruction::Nop { value: x },
                            Instruction::Nop { value: x } => Instruction::Jmp { value: x },
                            Instruction::Acc { .. } => { return None; }
                        };
                        // match whether it loops and it starts again or we get a success
                        match p.run(&instructions) {
                            (Termination::InfLoop, _) => None,
                            (Termination::End, j) => Some(j),
                        }
                    })
                    .unwrap()
}


fn main() -> Result<(), Box<dyn std::error::Error>> {
    let file = std::fs::read_to_string("data/input.txt").unwrap();

    // run program feeding in each line as a new instruction
    let instructions: Vec<Instruction> = file.split("\n")
                                             .filter(|line| !line.is_empty())
                                             .map(|s| s.parse::<Instruction>().unwrap())
                                             .collect();

    println!("part 1: {}", part1(&instructions));
    println!("part 2: {}", part2(&instructions));

    Ok(())
}