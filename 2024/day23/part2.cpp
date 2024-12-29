#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <sstream>
#include <iostream>

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

void find_maximal_cliques(
    const unordered_map<string, unordered_set<string>>& graph,
    unordered_set<string>& r,
    unordered_set<string>& p,
    unordered_set<string>& x,
    vector<string>& max_clique
) {
    if (p.empty() && x.empty()) {
        if (r.size() > max_clique.size())
            max_clique.assign(r.begin(), r.end());
        return;
    }

    string pivot;
    size_t maxi = 0;
    
    for (const auto& v : p) {
        if (graph.at(v).size() > maxi) {
            maxi = graph.at(v).size();
            pivot = v;
        }
    }
    
    for (const auto& v : x) {
        if (graph.at(v).size() > maxi) {
            maxi = graph.at(v).size();
            pivot = v;
        }
    }

    unordered_set<string> candidates = p;
    for (const auto& v : candidates) {
        if (graph.at(pivot).count(v) == 0) {
            p.erase(v);
            r.insert(v);
            
            unordered_set<string> newP, newX;            
            for (const auto& neighbor : graph.at(v)) {
                if (p.count(neighbor))
                    newP.insert(neighbor);
                if (x.count(neighbor))
                    newX.insert(neighbor);
            }
            
            find_maximal_cliques(graph, r, newP, newX, max_clique);
            
            r.erase(v);
            x.insert(v);
        }
    }
}

void part2(const vector<string>& input) 
{
    unordered_map<string, unordered_set<string>> g;
    
    for (const auto& line : input) {
        vector<string> parts = split(line, '-');
        string a = parts[0];
        string b = parts[1];
        g[a].insert(b);
        g[b].insert(a);
    }
    
    unordered_set<string> r;
    unordered_set<string> p;
    unordered_set<string> x;
    vector<string> max_clique;
    
    for (const auto& pair : g) {
        p.insert(pair.first);
    }
    
    find_maximal_cliques(g, r, p, x, max_clique);
    sort(max_clique.begin(), max_clique.end());
    
    string res;
    for (size_t i = 0; i < max_clique.size(); i++) {
        if (i > 0) res += ",";
        res += max_clique[i];
    }
    
    cout << "Part 2: " << res << endl;
}
