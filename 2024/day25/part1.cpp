#include <set>
#include <sstream>
#include "part1.hpp"

using namespace std;

pair<set<int>, bool> gridToSet(const vector<string>& grid) {
    set<int> points;
    int h = grid.size();
    
    if (h == 0)
        return {points, false};
    
    for (int r = 0; r < h; ++r) {
        const string& row = grid[r];
        for (string::size_type c = 0; c < row.length(); ++c) {
            if (row[c] == '#')
                points.insert(r * h + c);
        }
    }
    
    bool is_key = !grid.empty() && grid.back() == "#####";
    return {points, is_key};
}

int part1(const std::vector<std::string>& input) {
    vector<set<int>> locks;
    vector<set<int>> keys;
    
    vector<string> currentGrid;
    for (const auto& line : input) {
        if (line.empty()) {
            if (!currentGrid.empty()) {
                auto [points, is_key] = gridToSet(currentGrid);
                if (is_key)
                    keys.push_back(points);
                else 
                    locks.push_back(points);
                currentGrid.clear();
            }
        }
        else {
            currentGrid.push_back(line);
        }
    }
    
    if (!currentGrid.empty()) {
        auto [points, is_key] = gridToSet(currentGrid);
        if (is_key)
            keys.push_back(points);
        else
            locks.push_back(points);
    }
    
    int res = 0;
    for (const auto& lock : locks) {
        for (const auto& key : keys) {
            bool isDisjoint = true;
            for (int point : lock) {
                if (key.find(point) != key.end()) {
                    isDisjoint = false;
                    break;
                }
            }
            if (isDisjoint)
                res++;
        }
    }
    return res;
}
