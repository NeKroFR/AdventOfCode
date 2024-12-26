#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

#include "utils.hpp"

using namespace std;

long long part2(const vector<string> &input) {
    vector<long long> stones;
    for (const auto &line : input) {
        istringstream stream(line);
        long long num;
        while (stream >> num) {
            stones.push_back(num);
        }
    }
    return transform_stones(stones, 75);
}
