#include <vector>
#include <string>
#include <sstream>

using namespace std;


int part1(const std::vector<std::string> &input) 
{
    int safe = 0;
    
    for (const auto &line : input) {
        istringstream iss(line);
        vector<int> numbers;
        int number;
        while (iss >> number) {
            numbers.push_back(number);
        }
        
        bool inc = true;
        bool dec = true;
        
        for (size_t i = 1; i < numbers.size(); ++i) {
            int diff = numbers[i] - numbers[i-1];
            
            if (diff <= 0 || abs(diff) > 3)
                inc = false;
            
            if (diff >= 0 || abs(diff) > 3)
                dec = false;
        }
        
        if (inc || dec)
            safe++;
    }
    
    return safe;
}