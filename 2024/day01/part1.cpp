#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

int part1(const vector<string> &input) 
{
    vector<int> left, right;
    
    for (const auto &line : input) {
        istringstream iss(line);
        int l, r;
        if (iss >> l >> r) {
            left.push_back(l);
            right.push_back(r);
        }
    }
    
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    
    int res = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        res += abs(left[i] - right[i]);
    }
    
    return res;
}