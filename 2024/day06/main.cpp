#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

int main()
{
    vector<string> input = readInputFile("input.txt");
    cout << "+----------------------------+\n";
    cout << "| Advent of Code 2024 day 06 |\n";
    cout << "+----------------------------+\n";
    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;

    return 0;
}
