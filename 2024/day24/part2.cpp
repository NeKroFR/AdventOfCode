#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <regex>
#include <iostream>

using namespace std;

struct Dependency {
    string w1;
    string w2;
    string op;
    
    Dependency() = default;
    Dependency(const string& wire1, const string& wire2, const string& operation)
        : w1(wire1), w2(wire2), op(operation) {}
};

struct CircuitData {
    unordered_map<string, int> values;
    unordered_map<string, Dependency> deps;
    
    CircuitData() = default;
};

static CircuitData parse(const vector<string>& lines) {
    CircuitData data;
    bool readingValues = true;
    regex value_pattern("([a-zA-Z0-9]*): ([0-9])");
    regex instr_pattern("([a-z0-9]*) ([A-Z]*) ([a-z0-9]*) -> ([a-z0-9]*)");
    
    for (const auto& line : lines) {
        if (line.empty()) {
            readingValues = false;
            continue;
        }
        
        smatch matches;
        if (readingValues) {
            if (regex_match(line, matches, value_pattern))
                data.values[matches[1].str()] = stoi(matches[2].str());
        }
        else {
            if (regex_match(line, matches, instr_pattern)) {
                string w = matches[4].str();
                string w1 = matches[1].str();
                string op = matches[2].str();
                string w2 = matches[3].str();
                data.deps[w] = Dependency(w1, w2, op);
            }
        }
    }
    return data;
}

bool is_x_or_y(const string& wire) {
    if (wire.length() < 2)
        return false;
    char first = wire[0];
    if (first != 'x' && first != 'y')
        return false;
    try {
        int num = stoi(wire.substr(1));
        return num != 0;
    }
    catch (...) {
        return false;
    }
}

void part2(const vector<string>& input) {
    CircuitData data = parse(input);
    set<string> problematic_wires;

    for (const auto& [wire, dep] : data.deps) {
        if (wire[0] == 'z') {
            try {
                int val = stoi(wire.substr(1));
                if (dep.op != "XOR" && val != 45)
                    problematic_wires.insert(wire);
            }
            catch (...) {}
        }
        else if (!is_x_or_y(dep.w1) && !is_x_or_y(dep.w2) && 
                 !dep.w1.empty() && !dep.w2.empty() && 
                 dep.w1[0] != dep.w2[0] && dep.op == "XOR")
        {
            problematic_wires.insert(wire);
        }
        if (dep.op == "XOR" && is_x_or_y(dep.w1) && is_x_or_y(dep.w2) &&
            !dep.w1.empty() && !dep.w2.empty() && dep.w1[0] != dep.w2[0]) {
            bool found_valid = false;
            for (const auto& [_, other_dep] : data.deps) {
                if (other_dep.op == "XOR" && 
                    (other_dep.w1 == wire || other_dep.w2 == wire)) {
                    found_valid = true;
                    break;
                }
            }
            if (!found_valid)
                problematic_wires.insert(wire);
        }
        if (dep.op == "AND" && is_x_or_y(dep.w1) && is_x_or_y(dep.w2) &&
            !dep.w1.empty() && !dep.w2.empty() && dep.w1[0] != dep.w2[0])
        {
            bool found_valid = false;
            for (const auto& [_, other_dep] : data.deps) {
                if (other_dep.op == "OR" && 
                    (other_dep.w1 == wire || other_dep.w2 == wire)) {
                    found_valid = true;
                    break;
                }
            }
            if (!found_valid)
                problematic_wires.insert(wire);
        }
    }    
    vector<string> sorted_wires(problematic_wires.begin(), problematic_wires.end());
    sort(sorted_wires.begin(), sorted_wires.end());
    
    string res;
    for (const auto& wire : sorted_wires) {
        if (!res.empty()) res += ",";
            res += wire;
    }
    cout << "Part 2: " << res << endl;
}
