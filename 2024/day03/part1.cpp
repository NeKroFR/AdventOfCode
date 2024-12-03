#include <vector>
#include <string>
#include <regex>

using namespace std;

int part1(const std::vector<std::string> &input) 
{
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
