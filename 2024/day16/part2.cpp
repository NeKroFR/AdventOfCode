#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <limits>
#include <algorithm>

using namespace std;

typedef tuple<int, int, int, int, int, int, int> State;

typedef tuple<int, int, int> Key;
struct KeyHash {
    size_t operator()(const Key& k) const {
        return hash<int>()(get<0>(k)) ^ (hash<int>()(get<1>(k)) << 1) ^ (hash<int>()(get<2>(k)) << 2);
    }
};
typedef unordered_map<Key, vector<Key>, KeyHash> DepMap;

typedef pair<int, int> Position;
struct PairHash {
    size_t operator()(const Position& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

vector<string> parseInput(const vector<string>& input) {
    return input;
}

pair<pair<int, int>, pair<int, int>> findStartEnd(const vector<string>& grid) {
    int n = grid.size();
    pair<int, int> start, end;

    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 'S')
                start = {i, j};
            if (grid[i][j] == 'E')
                end = {i, j};
        }
    }
    return {start, end};
}

int dijkstra(const vector<string>& grid, pair<int,int> start, DepMap& deps, int& end_dir) {
    const vector<pair<int,int>> dd = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    priority_queue<State, vector<State>, greater<State>> pq;
    unordered_map<Key, int, KeyHash> cost;

    pq.push({0, 0, start.first, start.second, 0, start.first, start.second});

    while (!pq.empty()) {
        auto [c, d, i, j, pd, pi, pj] = pq.top();
        pq.pop();

        Key current = {d, i, j};
        if (cost.count(current)) {
            if (cost[current] == c)
                deps[current].emplace_back(pd, pi, pj);
            continue;
        }

        cost[current] = c;
        deps[current].emplace_back(pd, pi, pj);

        if (grid[i][j] == '#')
            continue;
        if (grid[i][j] == 'E') {
            end_dir = d;
            return c;
        }

        int ii = i + dd[d].first;
        int jj = j + dd[d].second;

        if (ii >= 0 && ii < static_cast<int>(grid.size()) && 
            jj >= 0 && jj < static_cast<int>(grid[0].size())) {
            pq.push({c + 1, d, ii, jj, d, i, j});
        }
        pq.push({c + 1000, (d + 1) % 4, i, j, d, i, j});
        pq.push({c + 1000, (d + 3) % 4, i, j, d, i, j});
    }
    return numeric_limits<int>::max();
}

int backtrack(const DepMap& deps, int end_dir, pair<int, int> end) {
    vector<Key> stack = {{end_dir, end.first, end.second}};
    unordered_set<Key, KeyHash> seen;
    unordered_set<Position, PairHash> seen_pos;

    while (!stack.empty()) {
        auto top = stack.back();
        stack.pop_back();

        if (seen.count(top))
            continue;
        seen.insert(top);
        seen_pos.insert({get<1>(top), get<2>(top)});

        if (deps.count(top)) {
            for (const auto& nbr : deps.at(top)) {
                stack.push_back(nbr);
            }
        }
    }
    return seen_pos.size();
}

int part2(const std::vector<std::string>& input) {
    vector<string> grid = parseInput(input);
    auto [start, end] = findStartEnd(grid);

    DepMap deps;
    int end_dir;
    dijkstra(grid, start, deps, end_dir);
    return backtrack(deps, end_dir, end);
}
