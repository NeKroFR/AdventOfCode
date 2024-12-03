#include <vector>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

int aux(const std::vector<std::string> &input) 
{
    // part1
    int res = 0;

    regex mul_pattern(R"(mul\((\d+),(\d+)\))");

    for (const auto& line : input) {

    sregex_iterator it(line.begin(), line.end(), mul_pattern);
    sregex_iterator end;    
    
    while (it != end) {
        int first = stoi((*it)[1]);
        int second = stoi((*it)[2]);    
        res += first * second;    
        ++it;
        }
    }

    return res;
}

int part2(const std::vector<std::string> &input) 
{
    bool read = true;
    std::vector<std::string> subset;

    for (const auto& line : input) {
        string subline;
        size_t i = 0;

        while (i < line.size()) {
            if (read) {
                if (i+6 < line.size() && line.substr(i, 7) == "don't()") {
                    read = false;
                    i += 7;
                } else {
                    subline += line[i];
                    i++;
                }
            } else {
                if (i+3 < line.size() && line.substr(i, 4) == "do()") {
                    read = true;
                    i += 4; 
                } else {
                    i++;
                }
            }
        }
        subset.push_back(subline);
    }
    /*
    // Debug 
    cout << "Subset:\n";
    for (const auto& line : subset) {
        cout << line << "\n";
    }
    */
    return aux(subset);
}