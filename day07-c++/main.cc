// You have a shiny gold bag. If you wanted to carry it in at least one other bag,
// how many different bag colors would be valid for the outermost bag? (In other words:
// how many colors can, eventually, contain at least one shiny gold bag?)

// part 1
// look for when shiny gold is mentioned, exclude if its the first two words
// add the parent bag to a list, iteratively check for that and future presences

// part 2
// How many individual bags are required inside your single shiny gold bag? 

#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <cassert>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <queue>

typedef std::tuple<int, std::string> bag;

std::unordered_map<std::string, std::vector<std::string>> reverse_rules(std::unordered_map<std::string, std::vector<bag>> &rules) {

    std::unordered_map<std::string, std::vector<std::string>> graph;

    for (auto rule : rules) {
        std::string parent_bag = rule.first;
        std::vector<bag> inner_bags = rule.second;

        for (bag b : inner_bags) {
            std::string inner_bag;
            tie(std::ignore, inner_bag) = b;

            if (graph.find(inner_bag) == graph.end()) {
                std::vector<std::string> parent_bags;
                graph[inner_bag] = parent_bags;
            }
            graph[inner_bag].push_back(parent_bag);
        }
    }
    return graph;
}

// part 1
int part1(std::unordered_map<std::string, std::vector<bag>> &rules, std::string color) {

    std::queue<std::string> bag_queue;
    bag_queue.push(color);

    std::unordered_set<std::string> discovered_bags;
    discovered_bags.insert(color);

    std::unordered_map<std::string, std::vector<std::string>> graph = reverse_rules(rules);
            
    while (!bag_queue.empty()) {
        std::string parent_bag = bag_queue.front();
        bag_queue.pop();
    
        for (std::string inner_bag : graph[parent_bag]) {
            if (discovered_bags.find(inner_bag) == discovered_bags.end()) {
                discovered_bags.insert(inner_bag);
                bag_queue.push(inner_bag);
            }
        }
    }
    return discovered_bags.size()-1; // the bag itself doesn't count
}

// part 2
int part2(std::unordered_map<std::string, std::vector<bag>> &rules, std::string color, std::unordered_map<std::string, int> &mem) {

    if (mem.find(color) == mem.end()) {
        int count = 1;
        std::vector<bag> inner = rules[color];
        
        for (bag b : inner) {
            int dupes;
            std::string c;
            tie(dupes, c) = b;
            count += dupes * part2(rules, c, mem);
        }
        mem[color] = count;
    }
    return mem[color];
}

int main() {
    std::string in_file("input.txt");
    std::ifstream in_file_stream(in_file.c_str());
    std::string line;

    std::unordered_map<std::string, std::vector<bag>> rules;

    std::regex first_bag_expr("(\\w+\\b \\w+\\b) bags");
    std::regex inner_bag_expr("(\\d) (\\w+\\b \\w+\\b) bags?");

    std::unordered_map<std::string, int> mem;

    // for each line
    // read the file and apply regex to get the bags and the bags within
    while(std::getline(in_file_stream, line)) {

        std::string first_bag;
        std::vector<bag> parent_bags;
        std::smatch match;

        // get all the bags and the bags within
        std::regex_search(line, match, first_bag_expr);
        first_bag = match[1]; // first bag in the line
        line = match.suffix();

        while (std::regex_search(line, match, inner_bag_expr)) {
            parent_bags.push_back(std::make_tuple(std::stoi(match[1]), match[2]));
            line = match.suffix();
        }
        rules[first_bag] = parent_bags;
    }

    std::cout << "part 1: " << part1(rules, "shiny gold") << std::endl;
    // the -1 is a janky fix
    std::cout << "part 2: " << part2(rules, "shiny gold", mem)-1 << std::endl;

    return 0;
}