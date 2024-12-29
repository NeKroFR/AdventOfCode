#include "part2.hpp"
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;


static long power(long x, long y) {
    return x^y;
}

static long prune(long x) {
    return x % 16777216;
}

static long next(long x) {
    x = prune(power(x, x * 64));
    x = prune(power(x, x / 32));
    x = prune(power(x, x * 2048));
    return x;
}

string format_change(long change) {
    stringstream ss;
    ss << std::showpos << change;
    return ss.str();
}

long part2(const vector<string>& input) {
    vector<vector<long>> sequences;
    vector<vector<long>> changes;
    
    for (const string& line : input) {
        long x = stol(line);
        vector<long> sequence = {x % 10};
        vector<long> change;

        for (int i = 0; i < 2000; i++) {
            long prev = x;
            x = next(x);
            sequence.push_back(x % 10);
            change.push_back(x % 10 - prev % 10);
        }
        
        sequences.push_back(sequence);
        changes.push_back(change);
    }
    
    vector<map<string, long>> quads; // quadriceps 🦵
    for (size_t x = 0; x < sequences.size(); x++) {
        map<string, long> quad; // https://www.youtube.com/watch?v=bJjCxjS7zTo
        for (int i = 3; i < 2000; i++) {
            string name = format_change(changes[x][i-3]) +
                         format_change(changes[x][i-2]) +
                         format_change(changes[x][i-1]) +
                         format_change(changes[x][i]);
            
            if (quad.find(name) == quad.end())
                quad[name] = sequences[x][i+1];
        }
        quads.push_back(quad);
    }
    
    map<string, long> sums;
    for (size_t x = 0; x < sequences.size(); x++) {
        for (const auto& [key, value] : quads[x]) {
            sums[key] = sums[key] + value;
        }
    }
    
    long maxi = 0;
    for (const auto& [key, value] : sums) {
        maxi = max(maxi, value);
    }
    return maxi;
}
