#include <vector>
#include <string>
#include <unordered_map>
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

long long resolve(const string& wire, CircuitData& data) {
    auto& values = data.values;
    const auto& deps = data.deps;
    
    if (values.find(wire) != values.end()) 
        return values[wire];
    
    const auto& dep = deps.at(wire);
    long long v1 = resolve(dep.w1, data);
    long long v2 = resolve(dep.w2, data);
    
    switch (dep.op[0]) {
        case 'X': // XOR
            values[wire] = v1 ^ v2;
            break;
        case 'A': // AND
            values[wire] = v1 & v2;
            break;
        case 'O':  // OR
            values[wire] = v1 | v2;
            break;
        default:
            throw invalid_argument(dep.op);
    }

    return values[wire];
}

long long part1(const vector<string>& input) {
    CircuitData data = parse(input);
    
    for (const auto& [wire, _] : data.deps) {
        resolve(wire, data);
    }
    
    long long res = 0;
    for (const auto& [wire, value] : data.values) {
        if (!wire.empty() && wire[0] == 'z') {
            try {
                int shift = stoi(wire.substr(1));
                res |= (long long)value << shift;
            }
            catch (...) {}
        }
    }
    return res;
}
