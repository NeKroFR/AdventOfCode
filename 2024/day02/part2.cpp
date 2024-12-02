#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool isSafe(const vector<int>& nums) {
    bool inc = true;
    bool dec = true;
    
    for (size_t i = 1; i < nums.size(); ++i) {
        int diff = nums[i] - nums[i-1];
        
        if (diff <= 0 || abs(diff) > 3)
            inc = false;
        if (diff >= 0 || abs(diff) > 3)
            dec = false;
        if (!inc && !dec)
            return false;
    }

    return inc || dec;
}


int part2(const std::vector<std::string> &input) 
{
    int safe = 0;
    
    for (const auto &line : input) {
        istringstream iss(line);
        vector<int> numbers;
        int number;
        while (iss >> number) {
            numbers.push_back(number);
        }
        
        if (isSafe(numbers)) {
            safe++;
            continue;
        }
        // bruteforcing the solution O(n^3) tho...
        bool safe_after = false;
        for (size_t i = 0; i < numbers.size(); ++i) {
            vector<int> modifiedNumbers = numbers;
            modifiedNumbers.erase(modifiedNumbers.begin() + i);
            
            if (isSafe(modifiedNumbers)) {
                safe_after = true;
                break;
            }
        }
        
        if (safe_after)
            safe++;
    }
    
    return safe;
}
