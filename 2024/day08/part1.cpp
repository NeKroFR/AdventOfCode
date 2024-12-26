#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>

using namespace std;

int part1(const vector<string>& grid) {
    map<char, vector<pair<int, int>>> antennas;
    set<pair<int, int>> anti_nodes;
    
    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] != '.') {
                antennas[grid[row][col]].push_back({static_cast<int>(row), static_cast<int>(col)});
            }
        }
    }
    
    for (const auto& antenna_group : antennas) {
        const auto& positions = antenna_group.second;
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = i + 1; j < positions.size(); j++) {
                const auto& pos1 = positions[i];
                const auto& pos2 = positions[j];
                
                int delta_row = pos2.first - pos1.first;
                int delta_col = pos2.second - pos1.second;
                
                pair<int, int> anti_node1 = {pos1.first - delta_row, pos1.second - delta_col};
                pair<int, int> anti_node2 = {pos2.first + delta_row, pos2.second + delta_col};
                
                if (anti_node1.first >= 0 && static_cast<size_t>(anti_node1.first) < grid.size() && 
                    anti_node1.second >= 0 && static_cast<size_t>(anti_node1.second) < grid[0].size()) {
                    anti_nodes.insert(anti_node1);
                }                
                if (anti_node2.first >= 0 && static_cast<size_t>(anti_node2.first) < grid.size() && 
                    anti_node2.second >= 0 && static_cast<size_t>(anti_node2.second) < grid[0].size()) {
                    anti_nodes.insert(anti_node2);
                }
            }
        }
    }
    return anti_nodes.size();
}