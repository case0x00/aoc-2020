# part 1
# The following rules are applied to every seat simultaneously:
# If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
# If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
# Otherwise, the seat's state does not change.
# Simulate your seating area by applying the seating rules repeatedly until no seats change state.
# How many seats end up occupied?
# part 2
# Now, instead of considering just the eight immediately adjacent seats, consider the first seat in each of
# those eight directions.
# Given the new visibility method and the rule change for occupied seats becoming empty,
# once equilibrium is reached, how many seats end up occupied?


function part1(seats::Array{Char,2})
    state_changed = true
    current_seats = collect(seats)
    # new seats is the result after a round
    new_seats = collect(seats)
    m,n = size(seats)

    while state_changed
        state_changed = false
        # for each row
        for i = 1:m
            # for each column
            for j = 1:n
                # if seat is actually a seat
                if current_seats[i,j] != '.'
                    # count occupied seats adjacent (3x3 square around the current element)
                    # eg for 2,2
                    # check [1,1; 1,2; 1,3;]; [2,1; (not 2,2); 2,3;]; [3,1; 3,2; 3,3;]
                    # check [-1,-1; -1,0; -1,+1;]; [0,-1; 0,0; 0,+1;]; [+1,-1; +1,0; +1,+1;];
                    c = 0
                    # for relative row
                    for p in (-1, 0, 1)
                        # for relative column
                        for q in (-1, 0, 1)
                            # 0,0 is the current element
                            if (q == 0 && p == 0)
                                continue
                            end
                            x = i + p # current row + relative shift
                            y = j + q # current column + relative shift
                            # x nor y can be negative or exceed the dimensions
                            if (x < 1 || x > size(seats)[1])
                                continue
                            end
                            if (y < 1 || y > size(seats)[2])
                                continue
                            end
                            if current_seats[x,y] == '#'
                                c += 1
                            end
                        end
                    end
                    # if seat is occupied and four or more are occupied -> empty
                    if current_seats[i,j] == '#' && c >= 4
                        new_seats[i,j] = 'L'
                        state_changed = true
                    # if seat is empty are there are no occupied seats -> occupied
                    elseif current_seats[i,j] == 'L' && c == 0
                        new_seats[i,j] = '#'
                        state_changed = true
                    end
                end
            end
        end
        copy!(current_seats, new_seats)
    end
    return count(i -> (i =='#'), current_seats)
end

# could reduce both functions given the similarities but w/e
function part2(seats::Array{Char,2})
    state_changed = true
    current_seats = collect(seats)
    # new seats is the result after a round
    new_seats = collect(seats)
    m,n = size(seats)

    while state_changed
        state_changed = false
        # for each row
        for i = 1:m
            # for each column
            for j = 1:n
                # if seat is actually a seat
                if current_seats[i,j] != '.'
                    # count occupied seats adjacent (3x3 square around the current element)
                    # eg for 2,2
                    # check [1,1; 1,2; 1,3;]; [2,1; (not 2,2); 2,3;]; [3,1; 3,2; 3,3;]
                    # check [-1,-1; -1,0; -1,+1;]; [0,-1; 0,0; 0,+1;]; [+1,-1; +1,0; +1,+1;];
                    c = 0
                    for p in (-1, 0, 1)
                        for q in (-1, 0, 1)
                            (p == 0 && q == 0) && continue
                            x, y = i, j
                            while true
                                x += p
                                y += q
                                !(x >= 1 && x <= size(current_seats)[1]) && break
                                !(y >= 1 && y <= size(current_seats)[2]) && break
                                if current_seats[x, y] == '#'
                                    c += 1
                                    break
                                elseif current_seats[x, y] == '.'
                                    continue
                                else
                                    break
                                end
                            end
                        end
                    end

                    # if seat is occupied and four or more are occupied -> empty
                    if current_seats[i,j] == '#' && c >= 5
                        new_seats[i,j] = 'L'
                        state_changed = true
                    # if seat is empty are there are no occupied seats -> occupied
                    elseif current_seats[i,j] == 'L' && c == 0
                        new_seats[i,j] = '#'
                        state_changed = true
                    end
                end
            end
        end
        copy!(current_seats, new_seats)
    end
    return count(i -> (i =='#'), current_seats)
end

# reading the input file
function read_file(path::String)
    s = open(path, "r") do file
        read(file, String)
    end
    return s
end

# collect solutions
function solutions(input::String)

    # loading the seats
    # not good for memory usage but oh well
    cseats = collect.(split(input))
    seats = reduce(vcat, permutedims.(collect.(split(input))))
#    println("part 1: ", part1(seats))
    println("part 2: ", part2(seats))

end

solutions(read_file("input.txt"))
