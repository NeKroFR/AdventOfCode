#include "part1.hpp"
#include <vector>
#include <string>

using namespace std;


static long power(long x, long y) {
    return x^y;
}

static long prune(long x) {
    return x % 16777216;
}

static long next(long x) {
    x = prune(power(x, x * 64));
    x = prune(power(x, x / 32));
    x = prune(power(x, x * 2048));
    return x;
}

long get_index(long seed, int idx) {
    long x = seed;
    for (int i = 0; i < idx; i++) {
        x = next(x);
    }
    return x;
}

long part1(const vector<string>& input) {
    long res = 0;
    for (const string& line : input) {
        long num = stoull(line);
        res += get_index(num, 2000);
    }
    return res;
}
