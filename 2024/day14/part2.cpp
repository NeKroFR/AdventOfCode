#include "part2.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <regex>
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

static vector<Robot> parseInput(const string& data) {
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

void move_robot(Robot& robot, const int width, const int height) {
    robot.x += robot.vel_x;
    while (robot.x < 0) {
        robot.x += width;
    }
    while (robot.x >= width) {
        robot.x -= width;
    }

    robot.y += robot.vel_y;
    while (robot.y < 0) {
        robot.y += height;
    }
    while (robot.y >= height) {
        robot.y -= height;
    }
}

int part2(const vector<string>& input) {
    const int width = 101;
    const int height = 103;

    ostringstream concatenated_data;
    for (const auto& line : input) {
        concatenated_data << line << "\n";
    }

    vector<Robot> robots = parseInput(concatenated_data.str());
    int res = 0;

    set<vector<pair<int, int>>> states;
    while (true) {
        res++;
        
        for (auto& robot : robots) {
            move_robot(robot, width, height);
        }

        vector<pair<int, int>> positions;
        for (const auto& robot : robots) {
            positions.emplace_back(robot.x, robot.y);
        }
        
        set<pair<int, int>> unique_positions(positions.begin(), positions.end());
        if (unique_positions.size() == positions.size())
            break;
            
        if (states.find(positions) != states.end())
            break;

        states.insert(positions);
    }

    ofstream outFile("tree.txt");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            bool found = false;
            for (const auto& robot : robots) {
                if (robot.x == j && robot.y == i) {
                    found = true;
                    break;
                }
            }
            outFile << (found ? "█" : " ");
        }
        outFile << "\n";
    }
    outFile.close();

    return res;
}