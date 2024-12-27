#include <vector>
#include <string>
#include <queue>
#include <map>
#include <utility>
#include <array>

using namespace std;

struct State {
    int score;
    int x;
    int y;
    int dir;
    
    bool operator>(const State& other) const {
        return score > other.score;
    }
};

int bfs(const vector<string>& maze, pair<int, int> start, pair<int, int> end) {
    const int rows = maze.size();
    const int cols = maze[0].size();
    
    const array<pair<int, int>, 4> dirs = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
    
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, start.first, start.second, 1});
    
    map<tuple<int, int, int>, int> visited;
    
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        
        if (make_pair(current.x, current.y) == end)
            return current.score;
        
        auto state_key = make_tuple(current.x, current.y, current.dir);
        if (visited.count(state_key) && visited[state_key] <= current.score)
            continue;
        
        visited[state_key] = current.score;
        
        int nx = current.x + dirs[current.dir].first;
        int ny = current.y + dirs[current.dir].second;
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] != '#')
            pq.push({current.score + 1, nx, ny, current.dir});
        
        for (int turn : {-1, 1}) {
            int new_dir = (current.dir + turn + 4) % 4;
            nx = current.x + dirs[new_dir].first;
            ny = current.y + dirs[new_dir].second;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] != '#')
                pq.push({current.score + 1001, nx, ny, new_dir});
        }
    }
    return -1;
}

int part1(const std::vector<std::string>& input) {
    pair<int, int> start, end;
    
    for (size_t i = 0; i < input.size(); ++i) {
        for (size_t j = 0; j < input[i].size(); ++j) {
            if (input[i][j] == 'S')
                start = {i, j};
            else if (input[i][j] == 'E')
                end = {i, j};
        }
    }
    return bfs(input, start, end);
}
