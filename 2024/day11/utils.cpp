#include <vector>
#include <unordered_map>
#include <string>
#include <utility> // for std::move

using namespace std;


long long transform_stones(const vector<long long> &stones, int blinks) {
    unordered_map<long long, long long> stones_count;

    for (const auto &stone : stones) {
        stones_count[stone]++;
    }

    for (int i = 0; i < blinks; ++i) {
        unordered_map<long long, long long> new_stones_count;

        for (const auto &[stone, count] : stones_count) {
            if (stone == 0)
                new_stones_count[1] += count;
            else if (to_string(stone).length() % 2 == 0) {
                string num_str = to_string(stone);
                int mid = num_str.length() / 2;
                long long left = stoll(num_str.substr(0, mid));
                long long right = stoll(num_str.substr(mid));
                new_stones_count[left] += count;
                new_stones_count[right] += count;
            }
            else
                new_stones_count[stone * 2024] += count;
        }

        stones_count = move(new_stones_count);
    }

    long long res = 0;
    for (const auto &[_, count] : stones_count) {
        res += count;
    }
    return res;
}
