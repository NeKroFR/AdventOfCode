#include <vector>
#include <string>
#include <regex>
#include <cstdint>
#include <iostream>
#include <sstream>

using namespace std;

struct Robot {
    int x;
    int y;
    int vel_x;
    int vel_y;
};

struct Position {
    int x;
    int y;
};

vector<Robot> parseInput(const string& data) {
    vector<Robot> robots;
    regex pattern(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");
    auto begin = sregex_iterator(data.begin(), data.end(), pattern);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        Robot robot;
        robot.x = stoi(match[1]);
        robot.y = stoi(match[2]);
        robot.vel_x = stoi(match[3]);
        robot.vel_y = stoi(match[4]);
        robots.push_back(robot);
    }
    return robots;
}

int part1(const std::vector<std::string> &input) {
    const int width = 101;
    const int height = 103;

    ostringstream concatenated_data;
    for (const auto& line : input) {
        concatenated_data << line << "\n";
    }

    vector<Robot> robots = parseInput(concatenated_data.str());
    vector<Position> final_positions;

    for (const auto& robot : robots) {
        Position pos;
        pos.x = ((robot.x + robot.vel_x * 100) % width + width) % width;
        pos.y = ((robot.y + robot.vel_y * 100) % height + height) % height;
        final_positions.push_back(pos);
    }

    const int center_x = width / 2;
    const int center_y = height / 2;

    vector<int> quads(4, 0);

    for (const auto& pos : final_positions) {
        if (pos.x == center_x && pos.y == center_y)
            continue;

        if (pos.x < center_x && pos.y < center_y)
            quads[0]++;
        else if (pos.x > center_x && pos.y < center_y)
            quads[1]++;
        else if (pos.x < center_x && pos.y > center_y)
            quads[2]++;
        else if (pos.x > center_x && pos.y > center_y)
            quads[3]++;
    }

    int res = 1;
    for (int num : quads) {
        res *= num;
    }
    return res;
}
