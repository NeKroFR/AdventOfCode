#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "part1.hpp"
#include "part2.hpp"

using namespace std;

vector<string> readInputFile(const string& filename) {
    vector<string> lines;
    ifstream file(filename);
    string line;
    
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return lines;
    }
    
    while (getline(file, line)) {
        lines.push_back(line);
    }
    
    return lines;
}


pair<vector<pair<int, int>>, vector<vector<int>>> getInput(const string& filename) {
    vector<pair<int, int>> rules;
    vector<vector<int>> updates;

    vector<string> input = readInputFile(filename);
    bool isRule = true;

    for (const string& line : input) {
        if (line.empty()) {
            isRule = false;
            continue;
        }

        if (isRule) {
            istringstream iss(line);
            int a, b;
            char delimiter;
            iss >> a >> delimiter >> b;
            rules.push_back(make_pair(a, b));
        } else {
            vector<int> numbers;
            istringstream iss(line);
            int number;
            while (iss >> number) {
                numbers.push_back(number);
                char comma;
                iss >> comma;
            }
            updates.push_back(numbers);
        }
    }

    return make_pair(rules, updates);
}
int main()
{
    auto [rules, updates] = getInput("input.txt");
    cout << "+----------------------------+\n";
    cout << "| Advent of Code 2024 day 05 |\n";
    cout << "+----------------------------+\n";
    cout << "Part 1: " << part1(rules, updates) << endl;
    cout << "Part 2: " << part2(rules, updates) << endl;
    
    return 0;
}
