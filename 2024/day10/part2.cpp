#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

using Memo = unordered_map<pair<int, int>, int, hash<pair<int, int>>>;

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        return hash<T1>()(p.first) ^ hash<T2>()(p.second);
    }
};

int count_paths(const vector<vector<int>> &G, int r, int c, unordered_map<pair<int, int>, int, pair_hash> &memo) {
    if (G[r][c] == 0)
        return 1;

    pair<int, int> key = {r, c};
    if (memo.count(key))
        return memo[key];

    int R = G.size();
    int C = G[0].size();
    int res = 0;

    for (const auto &[dr, dc] : vector<pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
        int rr = r + dr;
        int cc = c + dc;
        if (rr >= 0 && rr < R && cc >= 0 && cc < C && G[rr][cc] == G[r][c] - 1)
            res += count_paths(G, rr, cc, memo);
    }

    memo[key] = res;
    return res;
}

int part2(const std::vector<std::string> &input) {
    vector<vector<int>> G;
    for (const string &line : input) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0'); // to int
        }
        G.push_back(row);
    }

    int R = G.size();
    int C = G[0].size();
    int res = 0;

    unordered_map<pair<int, int>, int, pair_hash> memo;

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (G[r][c] == 9)
                res += count_paths(G, r, c, memo);
        }
    }
    return res;
}
