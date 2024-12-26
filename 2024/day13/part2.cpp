#include <vector>
#include <string>
#include <map>

using namespace std;

long long part2(const vector<string>& input) {
    vector<long long> prices;
    map<string, pair<long long, long long>> machine_data;
    
    for (const auto& line : input) {
        if (line.empty()) {
            if (!machine_data.empty()) {
                vector<long long> a = {machine_data["a"].first, machine_data["a"].second};
                vector<long long> b = {machine_data["b"].first, machine_data["b"].second};
                vector<long long> p = {machine_data["prize"].first, machine_data["prize"].second};
                
                p[0] += 10000000000000LL;
                p[1] += 10000000000000LL;
                
                long long denominator = (b[1] * a[0] - b[0] * a[1]);
                long long i = (p[0] * b[1] - b[0] * p[1]) / denominator;
                long long j = (p[1] - a[1] * i) / b[1];
                
                if (i >= 0 && j >= 0 && 
                    (a[0] * i + b[0] * j == p[0]) && 
                    (a[1] * i + b[1] * j == p[1])) {
                    prices.push_back(3 * i + j);
                }
                
                machine_data.clear();
            }
            continue;
        }

        if (line.find("Button A:") != string::npos) {
            long long x = stoll(line.substr(line.find("X+") + 2, line.find(",") - (line.find("X+") + 2)));
            long long y = stoll(line.substr(line.find("Y+") + 2));
            machine_data["a"] = {x, y};
        }
        else if (line.find("Button B:") != string::npos) {
            long long x = stoll(line.substr(line.find("X+") + 2, line.find(",") - (line.find("X+") + 2)));
            long long y = stoll(line.substr(line.find("Y+") + 2));
            machine_data["b"] = {x, y};
        }
        else if (line.find("Prize:") != string::npos) {
            long long x = stoll(line.substr(line.find("X=") + 2, line.find(",") - (line.find("X=") + 2)));
            long long y = stoll(line.substr(line.find("Y=") + 2));
            machine_data["prize"] = {x, y};
        }
    }

    if (!machine_data.empty()) {
        vector<long long> a = {machine_data["a"].first, machine_data["a"].second};
        vector<long long> b = {machine_data["b"].first, machine_data["b"].second};
        vector<long long> p = {machine_data["prize"].first, machine_data["prize"].second};
        
        p[0] += 10000000000000LL;
        p[1] += 10000000000000LL;
        
        long long denominator = (b[1] * a[0] - b[0] * a[1]);
        long long i = (p[0] * b[1] - b[0] * p[1]) / denominator;
        long long j = (p[1] - a[1] * i) / b[1];
        
        if (i >= 0 && j >= 0 && 
            (a[0] * i + b[0] * j == p[0]) && 
            (a[1] * i + b[1] * j == p[1])) {
            prices.push_back(3 * i + j);
        }
    }

    long long sum = 0;
    for (const auto& price : prices) {
        sum += price;
    }    
    return sum;
}