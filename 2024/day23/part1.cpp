#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>

using namespace std;

static vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

int part1(const vector<string> &input) 
{
    int res = 0;
    
    unordered_map<string, unordered_set<string>> g;
    
    for (const auto& line : input) {
        vector<string> parts = split(line, '-');
        string a = parts[0];
        string b = parts[1];
        g[a].insert(b);
        g[b].insert(a);
    }
    
    vector<string> vertices;
    for (const auto& pair : g) {
        vertices.push_back(pair.first);
    }
    
    for (size_t i = 0; i < vertices.size(); i++) {
        for (size_t j = i + 1; j < vertices.size(); j++) {
            for (size_t k = j + 1; k < vertices.size(); k++) {
                const string& a = vertices[i];
                const string& b = vertices[j];
                const string& c = vertices[k];
                
                if (a[0] == 't' || b[0] == 't' || c[0] == 't') {
                    if (g[a].count(b) && g[a].count(c) && g[b].count(c))
                        res++;
                }
            }
        }
    }
    return res;
}
