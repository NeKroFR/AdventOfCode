#include <vector>
#include <unordered_map>

using namespace std;

bool is_valid(const vector<int>& update, const vector<pair<int, int>>& rules) {
    unordered_map<int, int> idx;
    for (vector<int>::size_type i = 0; i < update.size(); ++i) {
        idx[update[i]] = i;
    }

    for (const auto& [a, b] : rules) {
        if (idx.count(a) && idx.count(b) && idx[a] > idx[b])
            return false;
    }
    return true;
}

int part1(const std::vector<std::pair<int, int>>& rules, const std::vector<std::vector<int>>& updates) {
    int res = 0;

    for (const auto& update : updates) {
        if (is_valid(update, rules))
            res += update[update.size() / 2];
    }
    return res;
}