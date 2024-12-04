#include <vector>
#include <string>
#include <set>

using namespace std;

int part2(const std::vector<std::string> &input) 
{
    int res = 0;
    set<char> validSet = {'M', 'S'};

    for (size_t i = 1; i < input.size() - 1; i++) {
        for (size_t j = 1; j < input[0].size() - 1; j++) {
            if (input[i][j] == 'A') {
                set<char> diag1 = {input[i-1][j-1], input[i+1][j+1]};
                set<char> diag2 = {input[i-1][j+1], input[i+1][j-1]};
                if (diag1 == validSet && diag2 == validSet)
                    res++;
            }
        }
    }

    return res;
}
