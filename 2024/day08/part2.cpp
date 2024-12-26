#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>

using namespace std;

int part2(const vector<string>& grid) {
    map<char, vector<pair<int, int>>> antennas;
    set<pair<int, int>> anti_nodes;
    
    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] != '.') {
                antennas[grid[row][col]].push_back({row, col});
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
                
                int anti_node1_row = pos1.first;
                int anti_node1_col = pos1.second;
                while (anti_node1_row >= 0 && static_cast<size_t>(anti_node1_row) < grid.size() && 
                       anti_node1_col >= 0 && static_cast<size_t>(anti_node1_col) < grid[0].size()) {
                    anti_nodes.insert({anti_node1_row, anti_node1_col});
                    anti_node1_row -= delta_row;
                    anti_node1_col -= delta_col;
                }
                
                int anti_node2_row = pos2.first;
                int anti_node2_col = pos2.second;
                while (anti_node2_row >= 0 && static_cast<size_t>(anti_node2_row) < grid.size() && 
                       anti_node2_col >= 0 && static_cast<size_t>(anti_node2_col) < grid[0].size()) {
                    anti_nodes.insert({anti_node2_row, anti_node2_col});
                    anti_node2_row += delta_row;
                    anti_node2_col += delta_col;
                }
            }
        }
    }
    
    return anti_nodes.size();
}