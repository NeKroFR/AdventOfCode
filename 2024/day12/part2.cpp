#include "part2.hpp"
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

inline bool in_grid(int i, int j, int n) {
    return (0 <= i && i < n) && (0 <= j && j < n);
}

int perim(const vector<pair<int, int>>& plot, int n) {
    set<pair<int, int>> plot_set(plot.begin(), plot.end());
    
    auto test = [&plot_set](const vector<pair<int, int>>& coords) {
        vector<int> res;
        for (const auto& coord : coords) {
            res.push_back(plot_set.count(coord));
        }
        return res;
    };
    
    int mini = 0, maxi = n;
    int minj = 0, maxj = n;
    
    for (const auto& [i, j] : plot) {
        mini = min(mini, i);
        maxi = max(maxi, i);
        minj = min(minj, j);
        maxj = max(maxj, j);
    }
    
    int result = 0;
    for (int i = mini-1; i <= maxi; i++) {
        for (int j = minj-1; j <= maxj; j++) {
            vector<pair<int, int>> coords = {
                {i,j}, {i,j+1}, {i+1,j}, {i+1,j+1}
            };
            auto res = test(coords);
            
            bool has_corner = false;
            bool has_double_corner = false;
            
            vector<vector<int>> corner_patterns = {
                {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1},
                {1,1,1,0}, {1,1,0,1}, {1,0,1,1}, {0,1,1,1}
            };
            vector<vector<int>> double_corner_patterns = {
                {1,0,0,1}, {0,1,1,0}
            };
            for (const auto& pattern : corner_patterns) {
                if (res == pattern) {
                    has_corner = true;
                    break;
                }
            }       
            for (const auto& pattern : double_corner_patterns) {
                if (res == pattern) {
                    has_double_corner = true;
                    break;
                }
            }
            result += has_corner + has_double_corner * 2;
        }
    }    
    return result;
}

int part2(const vector<string>& grid) {
    int n = grid.size();
    set<pair<int, int>> seen;
    vector<pair<char, vector<pair<int, int>>>> plots;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (seen.count({i, j})) continue;
            
            vector<pair<int, int>> stack = {{i, j}};
            plots.push_back({grid[i][j], vector<pair<int, int>>()});
            
            while (!stack.empty()) {
                auto [ci, cj] = stack.back();
                stack.pop_back();
                
                if (seen.count({ci, cj}))
                    continue;
                if (!in_grid(ci, cj, n))
                    continue;
                if (grid[ci][cj] != grid[i][j])
                    continue;

                seen.insert({ci, cj});
                plots.back().second.push_back({ci, cj});
                
                for (const auto& [di, dj] : directions) {
                    stack.push_back({ci + di, cj + dj});
                }
            }
        }
    }

    int res = 0;
    for (const auto& [c, plot] : plots) {
        res += perim(plot, n) * plot.size();
    }
    return res;
}