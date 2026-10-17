#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <numeric>
#include <utility>
#include <cstdint>

using namespace std;

const long long MOD = 998244353;

long long modpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n - 1);
        for (int i = 0; i < n - 1; i++) {
            cin >> a[i];
        }

        vector<long long> ans(n, 0);

        // TODO: calculate ans(i,j) for each player and round.
        // The solution requires counting permutations satisfying
        // the elimination rules and combining the results using XOR.

        cout << 0 << '\n';
    }

    return 0;
}