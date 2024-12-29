#include "part1.hpp"
#include <queue>
#include <unordered_map>
#include <limits>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

using Point = pair<int, int>;
using DistMap = unordered_map<Point, int, pair_hash>;

static DistMap bfs(const Point& start, 
            const vector<vector<char>>& grid, 
            bool through_walls = false,
            int max_steps = numeric_limits<int>::max()) {
    
    int h = grid.size();
    int w = grid[0].size();
    DistMap dist;
    dist[start] = 0;
    
    queue<pair<Point, int>> q;
    q.push({start, 0});
    
    const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    while (!q.empty()) {
        auto [pos, d] = q.front();
        q.pop();
        
        if (d == max_steps)
            continue;
        
        for (const auto& dir : directions) {
            int ny = pos.first + dir.first;
            int nx = pos.second + dir.second;
            Point next_pos(ny, nx);
            
            if (ny >= 0 && ny < h && nx >= 0 && nx < w && 
                dist.find(next_pos) == dist.end() && 
                (through_walls || grid[ny][nx] == '.')) {
                    
                dist[next_pos] = d + 1;
                q.push({next_pos, d + 1});
            }
        }
    }
    
    DistMap filtered_dist;
    for (const auto& [pos, val] : dist) {
        if (grid[pos.first][pos.second] == '.')
            filtered_dist[pos] = val;
    }
    return filtered_dist;
}

int part1(const std::vector<std::string>& lines) {
    vector<vector<char>> grid;
    for (const auto& line : lines) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }
    
    Point start, end;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'S')
                start = {i, j};
            if (grid[i][j] == 'E')
                end = {i, j};
        }
    }
    
    grid[start.first][start.second] = '.';
    grid[end.first][end.second] = '.';
    
    auto start_dists = bfs(start, grid);
    auto end_dists = bfs(end, grid);
    
    int normal_time = numeric_limits<int>::max();
    auto it = start_dists.find(end);
    if (it != start_dists.end())
        normal_time = it->second;
    
    vector<int> savings;
    set<Point> common_positions;
    
    for (const auto& [pos, _] : start_dists) {
        if (end_dists.find(pos) != end_dists.end())
            common_positions.insert(pos);
    }
    
    for (const auto& pos : common_positions) {
        auto cheat_dists = bfs(pos, grid, true, 2);
        for (const auto& [end_pos, cheat_steps] : cheat_dists) {
            if (end_dists.find(end_pos) != end_dists.end() && end_pos != pos) {
                int saving = normal_time - (start_dists[pos] + cheat_steps + end_dists[end_pos]);
                savings.push_back(saving);
            }
        }
    }
    
    int res = 0;
    for (const auto& saving : savings) {
        if (saving >= 100)
            res++;
    }
    return res;
}
