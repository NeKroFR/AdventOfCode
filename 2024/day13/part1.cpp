#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <map>

using namespace std;

int find_min_tokens(int a_x, int a_y, int b_x, int b_y, int prize_x, int prize_y) {
    int min_tokens = INT_MAX;

    // bruteforce until 100 presses
    for (int a_press = 0; a_press <= 100; ++a_press) {
        for (int b_press = 0; b_press <= 100; ++b_press) {
            if (a_press * a_x + b_press * b_x == prize_x && a_press * a_y + b_press * b_y == prize_y) {
                int tokens = a_press * 3 + b_press;
                min_tokens = min(min_tokens, tokens);
            }
        }
    }
    return min_tokens;
}

int part1(const vector<string>& input) {
    int total_tokens = 0;
    int prizes_won = 0;

    map<string, pair<int, int>> machine_data;
    for (size_t i = 0; i < input.size(); ++i) {
        const string& line = input[i];
        if (line.empty()) {
            if (!machine_data.empty()) {
                int a_x = machine_data["a"].first;
                int a_y = machine_data["a"].second;
                int b_x = machine_data["b"].first;
                int b_y = machine_data["b"].second;
                int prize_x = machine_data["prize"].first;
                int prize_y = machine_data["prize"].second;

                int tokens = find_min_tokens(a_x, a_y, b_x, b_y, prize_x, prize_y);
                if (tokens != INT_MAX) {
                    total_tokens += tokens;
                    prizes_won++;
                }
            }
            machine_data.clear();
            continue;
        }

        if (line.find("Button A:") != string::npos) {
            int x = stoi(line.substr(line.find("X+") + 2, line.find(",") - (line.find("X+") + 2)));
            int y = stoi(line.substr(line.find("Y+") + 2));
            machine_data["a"] = {x, y};
        }
        else if (line.find("Button B:") != string::npos) {
            int x = stoi(line.substr(line.find("X+") + 2, line.find(",") - (line.find("X+") + 2)));
            int y = stoi(line.substr(line.find("Y+") + 2));
            machine_data["b"] = {x, y};
        }
        else if (line.find("Prize:") != string::npos) {
            int x = stoi(line.substr(line.find("X=") + 2, line.find(",") - (line.find("X=") + 2)));
            int y = stoi(line.substr(line.find("Y=") + 2));
            machine_data["prize"] = {x, y};
        }
    }

    if (!machine_data.empty()) {
        int a_x = machine_data["a"].first;
        int a_y = machine_data["a"].second;
        int b_x = machine_data["b"].first;
        int b_y = machine_data["b"].second;
        int prize_x = machine_data["prize"].first;
        int prize_y = machine_data["prize"].second;

        int tokens = find_min_tokens(a_x, a_y, b_x, b_y, prize_x, prize_y);
        if (tokens != INT_MAX) {
            total_tokens += tokens;
            prizes_won++;
        }
    }
    return total_tokens;
}
