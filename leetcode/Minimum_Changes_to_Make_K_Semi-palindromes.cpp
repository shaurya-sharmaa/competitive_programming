class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        // Precompute proper divisors
        vector<vector<int>> divisors(n + 1);
        for (int d = 1; d <= n / 2; d++) {
            for (int len = 2 * d; len <= n; len += d) {
                divisors[len].push_back(d);
            }
        }
        // Calculate cost of every substring
        vector<vector<int>> cost(n, vector<int>(n, 0));
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                int len = r - l + 1;
                int best = len;
                for (int d : divisors[len]) {
                    int changes = 0;
                    int groups = len / d;
                    for (int offset = 0; offset < d; offset++) {
                        for (int t = 0; t < groups / 2; t++) {
                            int a = l + offset + t * d;
                            int b = l + offset + (groups - 1 - t) * d;
                            if (s[a] != s[b]) {
                                changes++;
                            }
                        }
                    }
                    best = min(best, changes);
                }
                cost[l][r] = best;
            }
        }
        // Dynamic programming
        const int INF = 1e9;
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;
        for (int segments = 1; segments <= k; segments++) {
            for (int end = 2 * segments; end <= n; end++) {
                for (int start = 2 * (segments - 1);
                     start <= end - 2; start++) {
                    if (dp[segments - 1][start] == INF) {
                        continue;
                    }
                    dp[segments][end] = min(
                        dp[segments][end],
                        dp[segments - 1][start] + cost[start][end - 1]
                    );
                }
            }
        }
        return dp[k][n];
    }
};