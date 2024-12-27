#include "part2.hpp"
#include <tuple>
#include <queue>
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

static tuple<vector<vector<char>>, int, int> resize_grid(const vector<vector<char>>& grid, int x, int y) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<char>> board(n, vector<char>(m * 2));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                board[i][j*2] = '#';
                board[i][j*2+1] = '#';
            }
            else if (grid[i][j] == 'O') {
                board[i][j*2] = '[';
                board[i][j*2+1] = ']';
            }
            else if (grid[i][j] == '.') {
                board[i][j*2] = '.';
                board[i][j*2+1] = '.';
            }
            else if (grid[i][j] == '@') {
                board[i][j*2] = '@';
                board[i][j*2+1] = '.';
            }
        }
    }
    return {board, x, y * 2};
}

int part2(const vector<string>& input) {
    auto [grid, seq] = parse(input);
    auto [rx, ry] = find_robot(grid);
    if (rx == -1 || ry == -1)
        return 0;
    
    auto [board, x, y] = resize_grid(grid, rx, ry);

    const vector<int> dx = {+1, -1, 0, 0};
    const vector<int> dy = {0, 0, +1, -1};
    int n = board.size();
    int m = board[0].size();

    for (char move : seq) {
        int dir = todir(move);
        if (dir == -1)
            continue;

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<pair<int, int>> q;
        vector<tuple<int, int, char>> save;
        bool empty = true;
        
        q.push(make_pair(x, y));
        visited[x][y] = true;

        while (!q.empty()) {
            int ax = q.front().first;
            int ay = q.front().second;
            q.pop();
            
            save.push_back(make_tuple(ax, ay, board[ax][ay]));
            
            int cx = ax + dx[dir];
            int cy = ay + dy[dir];
            
            if (cx < 0 || cx >= n || cy < 0 || cy >= m) {
                empty = false;
                break;
            }    
            if (board[cx][cy] == '#') {
                empty = false;
                break;
            }
            if (board[cx][cy] == '.' || visited[cx][cy])
                continue;
            
            q.push(make_pair(cx, cy));
            visited[cx][cy] = true;
            
            if (board[cx][cy] == '[') {
                if (cy + 1 < m) {
                    q.push(make_pair(cx, cy + 1));
                    visited[cx][cy + 1] = true;
                }
            }
            else if (board[cx][cy] == ']') {
                if (cy - 1 >= 0) {
                    q.push(make_pair(cx, cy - 1));
                    visited[cx][cy - 1] = true;
                }
            }
        }
        if (!empty)
            continue;

        while (!save.empty()) {
            auto [ax, ay, sym] = save.back();
            save.pop_back();
            
            int cx = ax + dx[dir];
            int cy = ay + dy[dir];
            
            board[ax][ay] = '.';
            board[cx][cy] = sym;
        }
        
        board[x][y] = '.';
        x = x + dx[dir];
        y = y + dy[dir];
        board[x][y] = '@';
    }
    
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '[')
                res += 100 * i + j;
        }
    }
    return res;
}