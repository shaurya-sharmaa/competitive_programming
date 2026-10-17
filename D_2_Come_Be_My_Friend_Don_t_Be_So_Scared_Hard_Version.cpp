#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <random>
#include <chrono>
using namespace std;

using ull = unsigned long long;
using Hash = pair<ull, ull>;

struct PairHash {
    size_t operator()(const Hash& p) const {
        ull x = p.first;
        ull y = p.second;
        x ^= y + 0x9e3779b97f4a7c15ULL + (x << 6) + (x >> 2);
        return static_cast<size_t>(x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937_64 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<Hash> events(n + 2, {0, 0});

        for (int i = 0; i < m; i++) {
            int l, r;
            cin >> l >> r;

            ull x = rng();
            ull y = rng();

            events[l].first ^= x;
            events[l].second ^= y;
            events[r + 1].first ^= x;
            events[r + 1].second ^= y;
        }

        unordered_map<Hash, vector<int>, PairHash> groups;
        groups.reserve(2 * n);

        Hash current = {0, 0};

        for (int i = 1; i <= n; i++) {
            current.first ^= events[i].first;
            current.second ^= events[i].second;
            groups[current].push_back(i);
        }

        vector<pair<int, int>> answer;
        answer.reserve(n / 2 + 1);

        for (const auto& entry : groups) {
            const vector<int>& positions = entry.second;
            int sz = static_cast<int>(positions.size());
            int k = (sz + 1) / 2;

            for (int j = 0; j < k; j++) {
                answer.push_back({
                    positions[j],
                    positions[j + k - 1]
                });
            }
        }

        cout << answer.size() << '\n';

        for (const auto& [l, r] : answer) {
            cout << l << ' ' << r << '\n';
        }
    }

    return 0;
}