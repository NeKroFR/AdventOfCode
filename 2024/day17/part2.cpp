#include "part2.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

long get_val(long a) {
    long d = (a % 8) ^ 5;
    long val = (d ^ (a / (1L << d)) ^ 6) % 8;
    return val;
}

long part2(const std::vector<std::string> &input) {
    vector<long> program;
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i].find("Program") != string::npos) {
            string nums = input[i].substr(input[i].find_last_of(" ") + 1);
            stringstream ss(nums);
            string num;
            while (getline(ss, num, ',')) {
                program.push_back(stol(num));
            }
            break;
        }
    }

    vector<long> res = {0};    
    for (auto it = program.rbegin(); it != program.rend(); ++it) {
        long p = *it;
        vector<long> tmp;
        
        for (long x : res) {
            for (long a = 0; a < 8; a++) {
                long val_to_check = (x << 3) + a;
                long val = get_val(val_to_check);
                if (val == p)
                    tmp.push_back(val_to_check);
            }
        }
        res = tmp;
    }
    
    if (res.empty())
        return 0;
    return *min(res.begin(), res.end());
}
