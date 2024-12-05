#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

pair<int, int> valid(const vector<int>& update, const vector<pair<int, int>>& rules) {
    unordered_map<int, int> idx;
    for (size_t i = 0; i < update.size(); ++i) {
        idx[update[i]] = i;
    }

    for (const auto& [a, b] : rules) {
        if (idx.count(a) && idx.count(b) && idx[a] > idx[b])
            return {idx[a], idx[b]};
    }
    return {-1, -1};
}

int part2(const std::vector<std::pair<int, int>>& rules, const std::vector<std::vector<int>>& updates) {
    int res = 0;
    bool add = false;
    for (auto update : updates) {
        pair<int, int> invalid_pair = valid(update, rules);
        add = invalid_pair != make_pair(-1, -1);
        while (invalid_pair.first != -1 && invalid_pair.second != -1) {
            swap(update[invalid_pair.first], update[invalid_pair.second]);
            invalid_pair = valid(update, rules);
        }
        if (add)
            res += update[update.size() / 2];
    }
    return res;
}
