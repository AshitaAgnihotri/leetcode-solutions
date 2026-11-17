class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Precompute minimum changes for every substring
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len <= n; l++) {
                int r = l + len - 1;

                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;

                    // Compare characters in each residue group
                    for (int rem = 0; rem < d; rem++) {
                        int left = l + rem;
                        int right = r - ((len - 1 - rem) % d);

                        while (left < right) {
                            if (s[left] != s[right])
                                changes++;

                            left += d;
                            right -= d;
                        }
                    }

                    cost[l][r] = min(cost[l][r], changes);
                }
            }
        }

        // DP
        vector<vector<int>> dp(n + 1,
                               vector<int>(k + 1, INF));

        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                for (int len = 2; len <= i; len++) {
                    int prev = i - len;

                    if (dp[prev][j - 1] == INF)
                        continue;

                    dp[i][j] = min(
                        dp[i][j],
                        dp[prev][j - 1] + cost[prev][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
