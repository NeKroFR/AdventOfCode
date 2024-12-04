#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

pair<unordered_map<int, vector<char>>, unordered_map<int, vector<char>>> 
find_diags(const vector<string>& data) {
    int lines = data.size();
    int cols = data[0].length();

    unordered_map<int, vector<char>> diag1;
    unordered_map<int, vector<char>> diag2;
    for (int l = 0; l < lines; l++) {
        for (int c = 0; c < cols; c++) {
            int k1 = l - c;
            diag1[k1].push_back(data[l][c]);

            int k2 = l + c;
            diag2[k2].push_back(data[l][c]);
        }
    }

    return {diag1, diag2};
}

int part1(const std::vector<std::string> &input){
    vector<string> lines = input;

    for (size_t i = 0; i < input[0].length(); i++) {
        string col;
        for (const auto& line : input) {
            col += line[i];
        }
        lines.push_back(col);
    }

    auto [diag1, diag2] = find_diags(input);
    for (const auto& [key, diag] : diag1) {
        lines.push_back(string(diag.begin(), diag.end()));
    }
    for (const auto& [key, diag] : diag2) {
        lines.push_back(string(diag.begin(), diag.end()));
    }

    int res = 0;
    for (const auto& line : lines) {
        size_t i = 0;
        while ((i = line.find("XMAS", i)) != string::npos) {
            res++;
            i++;
        }
        i = 0;
        while ((i = line.find("SAMX", i)) != string::npos) {
            res++;
            i++;
        }
    }

    return res;
}
