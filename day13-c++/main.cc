// part 1
// Each bus has an ID number that also indicates how often the bus leaves for the airport.
// Bus schedules are defined based on a timestamp that measures the number of minutes since
// some fixed reference point in the past. At timestamp 0, every bus simultaneously departed
// from the sea port. After that, each bus travels to the airport, then various other locations,
// and finally returns to the sea port to repeat its journey forever.
// The time this loop takes a particular bus is also its ID number: the bus with ID 5 departs
// from the sea port at timestamps 0, 5, 10, 15, and so on. The bus with ID 11 departs at
// 0, 11, 22,33, and so on.
// Your notes (your puzzle input) consist of two lines. The first line is your estimate of
// the earliest timestamp you could depart on a bus. The second line lists the bus IDs that are
// in service according to the shuttle company; entries that show x must be out of service,
// so you decide to ignore them.
// To save time once you arrive, your goal is to figure out the earliest bus you can take to the airport.
// (There will be exactly one such bus.)
// What is the ID of the earliest bus you can take to the airport multiplied by the number of minutes
// you'll need to wait for that bus?

// part 2
// The shuttle company is running a contest: one gold coin for anyone that can find the earliest timestamp
// such that the first bus ID departs at that time and each subsequent listed bus ID departs at that
// subsequent minute. (The first line in your input is no longer relevant.)
// What is the earliest timestamp such that all of the listed bus IDs depart at offsets matching their
// positions in the list?

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <cassert>

// part 1
// for each bus ID, the ID represents the wavelength propagated from time 0
// the time at which the buses depart are at TIME%ID == 0
// find the next after the baseline supplied
int part1() {
    std::string in_file("input_test.txt");
    std::ifstream in_file_stream(in_file.c_str());
    std::string line;

    // finding earliest time to depart
    int earliest_timestamp;
    std::getline(in_file_stream, line);
    earliest_timestamp = std::stoi(line);

    // finding bus IDs
    std::vector<int> bus_ids;
    while (std::getline(in_file_stream, line, ',')) {
        int bus;
        std::stringstream ss(line);
        if (ss >> bus) {
            bus_ids.push_back(bus);
        }
    }

    size_t bus_i = 0;
    // eta for first bus as a baseline
    // eta is from current to bus departure
    int departure = bus_ids[bus_i] - earliest_timestamp % bus_ids[bus_i];
    for (size_t i = 1; i < bus_ids.size(); ++i) {
        // finding if there is a bus that leaves sooner
        // if so, set as new baseline
        if (bus_ids[i] - earliest_timestamp % bus_ids[i] < departure) {
            departure = bus_ids[i] - earliest_timestamp % bus_ids[i];
            bus_i = i;
        }
    }
    return bus_ids[bus_i] * departure;
}

// for part 2
// extended euclidean algorithm
//std::tuple<int64_t, int64_t, int64_t> extended_gcd(int64_t a, int64_t b) {
//    if (a == 0) { return std::make_tuple(b, 0, 1); }
//    int64_t gcd, x, y;
//    std::tie(gcd, x, y) = extended_gcd(b % a, a);
//    return std::make_tuple(gcd, y - ((b / a) * x), x);
//}


// part 2
int64_t part2() {
    std::string in_file("input.txt");
    std::ifstream in_file_stream(in_file.c_str());
    std::string line;

    // finding earliest time to depart
    int earliest_timestamp;
    std::getline(in_file_stream, line);
    earliest_timestamp = std::stoi(line);
    int offset = 0;
    std::vector<std::pair<int, int>> buses;

    // finding bus IDs
    while (std::getline(in_file_stream, line, ',')) {
        int bus;
        std::stringstream ss(line);
        if (ss >> bus) {
            buses.emplace_back(bus, offset);
        }
        ++offset;
    }

    if (buses.size() <= 1) {
        return 1;
    }

    size_t increment = 1;
	size_t n0 = 0;
	auto b0 = buses[0];
	for (size_t i = 1; i < buses.size(); ++i) {
		while ((b0.first * n0 - b0.second + buses[i].second) % buses[i].first != 0)
			n0 += increment;
		increment *= buses[i].first;
	}
    
    return b0.first * n0 - b0.second;
}



// part 2
// chinese remainder theorem
// is highly unstable for some reason? might be a data type problem
//int64_t part2() {
//    std::string in_file("input_test.txt");
//    std::ifstream in_file_stream(in_file.c_str());
//    std::string line;
//
//    // finding earliest time to depart
//    int earliest_timestamp;
//    std::getline(in_file_stream, line);
//    earliest_timestamp = std::stoi(line);
//    int offset = 0;
//    std::vector<int64_t> bi;
//
//    // finding bus IDs
//    std::vector<int64_t> bus_ids;
//    while (std::getline(in_file_stream, line, ',')) {
//        int bus;
//        std::stringstream ss(line);
//        if (ss >> bus) {
//            bus_ids.push_back(bus);
//            bi.push_back(bus - (offset % bus));
//        }
//        ++offset;
//    }
//
//    // N = n1*n2*n3*...*nk
//    int64_t N = std::accumulate(begin(bus_ids), end(bus_ids), (int64_t)1, std::multiplies<int64_t>());
//    // compute x for which it is a solution for all the remainder equations
//    // chinese remainder theorem helps collapse them all into one equation
//    // x = sum of all bi*ni*xi
//    int64_t x = 0;
//    for (int i = 0; i < bus_ids.size(); ++i) {
//        int64_t Ni = N / bus_ids[i];
//        std::tuple<int64_t, int64_t, int64_t> t = extended_gcd(Ni, bus_ids[i]);
//        int64_t gcd = std::get<0>(t);
//        int64_t xi = std::get<1>(t);
//        int64_t n = std::get<2>(t);
//        assert(gcd == 1);
//        x = (N + x + (bi[i] * Ni * xi)) % N;
////        std::cout << x << std::endl;
//    }
//    return x;
//}

// given the file must be parsed in 2 different ways, its been moved out of main
int main() {
    // part 1
    //std::cout << "part 1: " << part1() << std::endl;

    // part 2
    std::cout << "part 2: " << part2() << std::endl;
    return 0;
}