#include <vector>
#include <string>
#include <queue>
#include <set>
#include <utility>

using namespace std;

int count_paths(const vector<vector<int>> &G, int sr, int sc) {
    int R = G.size();
    int C = G[0].size();
    queue<pair<int, int>> Q;
    set<pair<int, int>> SEEN;
    Q.push({sr, sc});
    int res = 0;

    while (!Q.empty()) {
        auto [r, c] = Q.front();
        Q.pop();

        if (SEEN.count({r, c}))
            continue;
        SEEN.insert({r, c});

        if (G[r][c] == 0)
            res++;

        for (const auto &[dr, dc] : vector<pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
            int rr = r + dr;
            int cc = c + dc;
            if (rr >= 0 && rr < R && cc >= 0 && cc < C && G[rr][cc] == G[r][c] - 1) {
                Q.push({rr, cc});
            }
        }
    }
    return res;
}

int part1(const std::vector<std::string> &input) {
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

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (G[r][c] == 9)
                res += count_paths(G, r, c);
        }
    }
    return res;
}
