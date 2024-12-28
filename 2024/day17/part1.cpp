#include "part1.hpp"
#include <regex>
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

vector<int> extract_ints(const string& s) {
    vector<int> numbers;
    regex pattern("-?\\d+");
    
    auto begin = sregex_iterator(s.begin(), s.end(), pattern);
    auto end = sregex_iterator();
    
    for (sregex_iterator i = begin; i != end; ++i) {
        numbers.push_back(stoi(i->str()));
    }
    return numbers;
}

int combo(int n, int A, int B, int C) {
    switch (n) {
        case 0: case 1: case 2: case 3:
            return n;
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
        case 7:
            return 0;
        default:
            assert(false);
            return -1;
    }
}

vector<int> solve(const vector<string>& lines) {
    if (lines.empty())
        return {-1};

    int A = extract_ints(lines[0])[0];
    int B = extract_ints(lines[1])[0];
    int C = extract_ints(lines[2])[0];
    vector<int> Program = extract_ints(lines[4]);
    int ip = 0;

    vector<int> out;
    while (ip < static_cast<int>(Program.size())) {
        int opcode = Program[ip];
        int operand = (ip + 1 < static_cast<int>(Program.size())) ? Program[ip + 1] : 0;

        switch (opcode) {
            case 0: { // adv
                int power = combo(operand, A, B, C);
                A /= static_cast<int>(pow(2, power));
                break;
            }
            case 1: // bxl
                B ^= operand;
                break;
            case 2: // bst
                B = combo(operand, A, B, C) % 8;
                break;
            case 3: // jnz
                if (A != 0) {
                    ip = operand;
                    continue;
                }
                break;
            case 4: // bxc
                B ^= C;
                break;
            case 5: { // out
                int val = combo(operand, A, B, C) % 8;
                out.push_back(val);
                break;
            }
            case 6: { // bdv
                int power = combo(operand, A, B, C);
                B = A / static_cast<int>(pow(2, power));
                break;
            }
            case 7: { // cdv
                int power = combo(operand, A, B, C);
                C = A / static_cast<int>(pow(2, power));
                break;
            }
        }
        ip += 2;
    }
    return out;
}

void part1(const std::vector<std::string>& input) {
    auto result = solve(input);
    cout << "part1: ";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1)
            cout << ",";
    }
    cout << endl;
}
