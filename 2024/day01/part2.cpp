#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

int part2(const vector<string> &input) 
{
    vector<int> left;
    unordered_map<int, int> right;

    for (const auto &line : input) {
        istringstream iss(line);
        int l, r;
        if (iss >> l >> r) {
            left.push_back(l);
            right[r]++;
        }
    }

    int res = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        res += left[i] * right[left[i]];
    }
    return res;
}