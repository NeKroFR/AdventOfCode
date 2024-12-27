#include "part1.hpp"
#include <utility>

using namespace std;

static pair<vector<vector<char>>, string> parse(const vector<string>& input) {
    vector<vector<char>> grid;
    string seq;
    bool flag = false;

    for (const string& line : input) {
        if (line.empty()) {
            flag = true;
            continue;
        }
        if (flag)
            seq += line;
        else
            grid.push_back(vector<char>(line.begin(), line.end()));
    }
    return {grid, seq};
}

static pair<int, int> find_robot(const vector<vector<char>>& grid) {
    for (int i = 0; i < (int)grid.size(); i++) {
        for (int j = 0; j < (int)grid[i].size(); j++) {
            if (grid[i][j] == '@')
                return {i, j};
        }
    }
    return {-1, -1};
}

static int todir(char c) {
    switch (c) {
        case 'v': return 0;
        case '^': return 1;
        case '>': return 2;
        case '<': return 3;
        default: return -1;
    }
}

int part1(const vector<string>& input) {
    auto [grid, seq] = parse(input);
    auto [x, y] = find_robot(grid);
    if (x == -1 || y == -1)
        return 0;

    const vector<int> dx = {+1, -1, 0, 0};
    const vector<int> dy = {0, 0, +1, -1};

    for (char move : seq) {
        int dir = todir(move);
        if (dir == -1)
            continue;

        int cnt = 0;
        bool empty = true;
        
        while (true) {
            int cx = x + dx[dir] * (cnt + 1);
            int cy = y + dy[dir] * (cnt + 1);
            
            if (cx < 0 || cx >= (int)grid.size() || cy < 0 || cy >= (int)grid[0].size()) {
                empty = false;
                break;
            }       
            if (grid[cx][cy] == '.')
                break;
            if (grid[cx][cy] == '#') {
                empty = false;
                break;
            }
            cnt++;
        }
        
        if (!empty)
            continue;
        
        for (int i = 0; i < cnt; i++) {
            int cx = x + dx[dir] * (i + 2);
            int cy = y + dy[dir] * (i + 2);
            grid[cx][cy] = 'O';
        }
        grid[x][y] = '.';
        x = x + dx[dir];
        y = y + dy[dir];
        grid[x][y] = '@';
    }

    int res = 0;
    for (int i = 0; i < (int)grid.size(); i++) {
        for (int j = 0; j < (int)grid[i].size(); j++) {
            if (grid[i][j] == 'O')
                res += 100 * i + j;
        }
    }
    return res;
}
