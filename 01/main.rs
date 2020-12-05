// part 1
// Specifically, they need you to find the two entries that
// sum to 2020 and then multiply those two numbers together.

#[allow(dead_code)]
fn part_1(file_vec: Vec<i32>) -> i32 {
    let n = file_vec.len();
    // iterates through the vector
    for i in 0..n-1 {
        // iterates through the rest of the vector for each value
        for j in i+1..n {
            // if sum is 2020, multiply
            if file_vec[i] + file_vec[j] == 2020 {
                return file_vec[i] * file_vec[j];
            }
        }
    }
    return 0;
}


// part 2
// They offer you a second one if you can find three numbers
// in your expense report that meet the same criteria.

#[allow(dead_code)]
fn part_2(file_vec: Vec<i32>) -> i32 {
    let n = file_vec.len();
    // iterates through the vector
    for i in 0..n-2 {
        for j in i+1..n-1 {
            for k in j+1..n {
                if file_vec[i] + file_vec[j] + file_vec[k] == 2020 {
                    return file_vec[i] * file_vec[j] * file_vec[k];
                }
            }
        }
    }
    return 0;
}

// main to parse text file
// read the entire text file to a string
fn main() {
    let pattern = std::env::args().nth(1).expect("no file given");
    let input = std::fs::read_to_string(pattern).unwrap();
    let x = input.split("\n").map(|s| s.parse::<i32>().unwrap()).collect::<Vec<_>>();
//    println!("{:?}", x)
//    println!("part 1 soln: {}", part_1(x))
    println!("part 2 soln: {}", part_2(x))

}