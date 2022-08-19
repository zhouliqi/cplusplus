#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;


template <typename K, typename F = std::hash<K>>
class LogLog {
private:
    const int M = 11;
    const double C = 0.79402;

    vector<uint> buckets_;

    F hash_;

public:
    explicit LogLog() : buckets_(vector<uint>(1 << M, 0)) {}

    inline void insert(const K& key) {
        size_t val = hash_(key);
        size_t index = val >> (64 - M);
        uint count = 0;
        while ((val & 1) == 0 && count < (64 - M)) {
            ++count;
            val >>= 1;
        }
        buckets_[index] = max(buckets_[index], count);
    }

    double cardinality() {
        auto sum = std::accumulate(buckets_.begin(), buckets_.end(), 0);
        return 1.0 * C * (1 << M) * std::pow(2.0, 1.0 * sum / (1 << M));
    }
};


int main() {
    size_t n = 1e4;
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(0, n);

    string key = "key";
    vector<string> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = key + to_string(dist(rng));
    }

    unordered_set<string> s(nums.begin(), nums.end());

    LogLog<string> loglog;
    for (string& x : nums) {
        loglog.insert(x);
    }

    cout << "Hashmap count: " << s.size() << "\n";
    cout << "LogLog algorithm: " << loglog.cardinality() << "\n";

    return 0;
}