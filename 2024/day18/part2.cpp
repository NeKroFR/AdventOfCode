#include "part2.hpp"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

void part2(const vector<string>& input) {
    const int N = 70;
    const vector<pair<int, int>> dd = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    
    vector<pair<int, int>> coords;
    for (const auto& line : input) {
        istringstream iss(line);
        int x, y;
        char comma;
        if (iss >> x >> comma >> y)
            coords.push_back({x, y});
    }

    auto h = [N](int i, int j) -> int {
        return abs(N - i) + abs(N - j);
    };

    auto doable = [N, &coords, &dd, &h](int idx) -> bool {
        auto in_grid = [N, &coords, idx](int i, int j) -> bool {
            if (!(0 <= i && i <= N && 0 <= j && j <= N))
                return false;
            for (int k = 0; k < idx; k++) {
                if (coords[k].first == i && coords[k].second == j)
                    return false;
            }
            return true;
        };

        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > q;
        
        unordered_map<pair<int, int>, int, PairHash> cost;

        q.push({h(0, 0), {0, 0}});

        while (!q.empty()) {
            auto current = q.top();
            q.pop();
            
            int c = current.first;
            auto pos = current.second;
            int i = pos.first;
            int j = pos.second;

            if (cost.find({i, j}) != cost.end())
                continue;

            cost[{i, j}] = c - h(i, j);

            if (i == N && j == N)
                return true;

            for (const auto& d : dd) {
                int ii = i + d.first;
                int jj = j + d.second;
                
                if (in_grid(ii, jj)) {
                    int new_cost = cost[{i, j}] + 1;
                    q.push({new_cost + h(ii, jj), {ii, jj}});
                }
            }
        }
        return false;
    };

    int lo = 0;
    int hi = coords.size() - 1;
    
    while (hi > lo) {
        int mid = (lo + hi) / 2;
        if (doable(mid))
            lo = mid + 1;
        else
            hi = mid;
    }
    cout << "Part 2: " << coords[lo-1].first << "," << coords[lo-1].second << endl;
}
