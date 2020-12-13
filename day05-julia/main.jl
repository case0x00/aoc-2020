# seat arrangement uses binary space partitioning where
# F is front, B is back, L is left, and R is right
# first 7 chars are either F or B which specify which row (0-127)
# each letter states which half of a region the given seat is in
# last 3 chars are either L or R which specify which column (0-7)
# with the same process being used
# each seat has a unique id: multiply row by 8, add column

# eg. FBFBBFFRLR states:
# F (0-63)
# B (32-63)
# F (32-47)
# B (40-47)
# B (44-47)
# F (44-45)
# F (44) -> seat at row 44
# R (4-7)
# L (4-5)
# R(5) -> seat at column 5
# thus FBFBBFFRLR is a seat at row 44, column 5 with unique id 357

# part 1
# what is the highest seat id on a boarding pass

# part 2
# It's a completely full flight, so your seat should be the
# only missing boarding pass in your list. However, there's a catch:
# some of the seats at the very front and back of the plane don't
# exist on this aircraft, so they'll be missing from your list as well.


# reading the input file
function read_file(path::String)
    s = open(path, "r") do file
        read(file, String)
    end
    return s
end

# binary space partitioning for an individual sequence
function bin_space_part(sequence::AbstractString,
                        lims::Array{Int, 1},
                        chars::Array{Char, 1},
                        seq_lims::Array{Int, 1})::Int

    # lims is limit to number of columns or rows
    low = lims[1]
    high = lims[2]
    # seq_lims is the limit to the sub-sequence (7 chars for row, 3 for column)
    for i = seq_lims[1]:seq_lims[2]
        # ÷ is to ensure rounding
        mid = low + (high - low) ÷ 2
        if sequence[i] == chars[1]
            high = mid
        elseif sequence[i] == chars[2]
            low = mid + 1
        end
    end
    return low
end

# a little janky having this fn but i need to parse the col and row
# at the same time for every sequence
function get_seat_id(sequence::AbstractString)::Int
    # '' denotes char
    col = bin_space_part(sequence, [0, 127], ['F', 'B'], [1, 7])
    row = bin_space_part(sequence, [0, 7], ['L', 'R'], [8, 10])

    return col * 8 + row
end

# find the missing seat
function get_missing_seat(seats::Array{Int, 1})::Int
    
    # min seat is obv 0
    min_seat = 0
    # max seat uses the formula 'multiply row by 8, add column'
    max_seat = 127 * 8 + 7

    # loops through all possible seats
    for i = min_seat:max_seat
        # if a possible seat doesnt appear in our list
        if !(i in seats)
            # and if it is not at the back or front
            if (i-1) in seats && (i+1) in seats
                # then it is ours
                return i
            end
        end
    end
end

function solutions(input::String)
    seat_ids = [get_seat_id(seq) for seq in split(input)]

    # part 1
    max_seat_id = maximum(seat_ids)
    println("part 1: ", max_seat_id)

    # part 2
    println("Part 2: ", get_missing_seat(seat_ids))
end

solutions(read_file("input.txt"))