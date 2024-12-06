#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int part1(const std::vector<std::string> &input)
{
    int x = 0;
    int y = 0;
    int n = static_cast<int>(input.size());
    int m = static_cast<int>(input[0].size());
    while (x < n) {
        while (y < m) {
            if (input[x][y] == '^')
                break;
            y++;
        }
        if (y < static_cast<int>(input[x].size()) && input[x][y] == '^')
            break;
        x++;
        y = 0;
    }
    
    int dir = 0;
    vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // up: 0, right: 1, down: 2, left: 3
    unordered_set<string> visited;
    visited.insert(to_string(x) + "," + to_string(y));
    
    for (;;) {
        int nx = x + dirs[dir].first;
        int ny = y + dirs[dir].second;

        if (nx < 0 || nx >= static_cast<int>(input.size()) || 
            ny < 0 || ny >= static_cast<int>(input[0].size())) {
            break;
        }

        if (input[nx][ny] == '#')
            dir = (dir + 1) % 4; 
        else {
            x = nx;
            y = ny;
            visited.insert(to_string(x) + "," + to_string(y));
        }
    }

    return visited.size();
}