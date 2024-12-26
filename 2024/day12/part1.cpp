#include <vector>
#include <string>
#include <unordered_set>
#include <stack>
#include <iostream>
#include <sstream>

using namespace std;

bool in_grid(int i, int j, int n) {
    return (0 <= i && i < n) && (0 <= j && j < n);
}

int perim(const vector<pair<int, int>>& plot, const vector<string>& grid, const vector<vector<int>>& directions, int n) {
    int res = 0;
    for (const auto& [i, j] : plot) {
        for (const auto& dir : directions) {
            int ni = i + dir[0];
            int nj = j + dir[1];
            if (!in_grid(ni, nj, n) || grid[ni][nj] != grid[i][j])
                res++;
        }
    }
    return res;
}

int part1(const vector<string>& input) {
    int n = input.size();
    vector<vector<int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    unordered_set<string> seen;
    vector<vector<pair<int, int>>> plots;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (seen.count(to_string(i) + "," + to_string(j)))
                continue;

            stack<pair<int, int>> stack;
            stack.push({i, j});
            plots.push_back({});

            while (!stack.empty()) {
                auto [ci, cj] = stack.top();
                stack.pop();
                if (seen.count(to_string(ci) + "," + to_string(cj)) || !in_grid(ci, cj, n) || input[ci][cj] != input[i][j])
                    continue;

                seen.insert(to_string(ci) + "," + to_string(cj));
                plots.back().push_back({ci, cj});

                for (const auto& dir : directions) {
                    stack.push({ci + dir[0], cj + dir[1]});
                }
            }
        }
    }
    int res = 0;
    for (const auto& plot : plots) {
        res += perim(plot, input, directions, n) * plot.size();
    }
    return res;
}
