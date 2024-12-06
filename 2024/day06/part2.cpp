#include <vector>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <iostream>

using namespace std;

typedef pair<int, int> Position;
typedef map<Position, char> LabMap;

pair<set<Position>, bool> simulate(Position guard, const LabMap &lab_map) {
    vector<Position> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // up, right, down, left
    int dir = 0;
    set<Position> visited;
    set<pair<Position, int>> visited_cycle;
    bool is_cycle = false;

    while (true) {
        visited.insert(guard);
        if (visited_cycle.find({guard, dir}) != visited_cycle.end()) {
            is_cycle = true;
            break;
        }
        else {
            visited_cycle.insert({guard, dir});
        }

        int i = guard.first;
        int j = guard.second;
        int di = directions[dir].first;
        int dj = directions[dir].second;
        Position next = {i + di, j + dj};

        if (lab_map.find(next) == lab_map.end())
            break;
        else if (lab_map.at(next) == '#')
            dir = (dir + 1) % 4;
        else
            guard = next;
    }
    return {visited, is_cycle};
}

pair<Position, LabMap> parse(const vector<string> &input) {
    Position guard = {-1, -1};
    LabMap lab;

    int x = 0;
    int y = 0;
    int n = static_cast<int>(input.size());
    int m = static_cast<int>(input[0].size());

    while (x < n) {
        while (y < m) {
            if (input[x][y] == '^') {
                guard = {x, y};
                break;
            }
            y++;
        }
        if (guard.first != -1 && guard.second != -1)
            break;
        x++;
        y = 0;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char current = input[i][j];
            if (current == '^')
                lab[{i, j}] = '.';
            else
                lab[{i, j}] = current;
        }
    }

    return {guard, lab};
}


int part2(const vector<string> &input) {
    auto [guard, lab] = parse(input);

    auto [possible_obstacles, _] = simulate(guard, lab);
    possible_obstacles.erase(guard);

    set<Position> obstacles;
    for (const auto &candidate : possible_obstacles) {
        LabMap new_lab = lab;
        new_lab[candidate] = '#';
        auto [_, is_cycle] = simulate(guard, new_lab);
        if (is_cycle)
            obstacles.insert(candidate);
    }

    return obstacles.size();
}
