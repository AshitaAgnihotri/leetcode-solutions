class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;

        vector<vector<long long>> dp(n + k, vector<long long>(2 * k + 1, 0));

        for (int i = 0; i <= n + k - 1; i++) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= n + k - 1; i++) {
            for (int j = 1; j <= 2 * k; j++) {
                dp[i][j] = dp[i - 1][j];

                if (i >= j) {
                    dp[i][j] += dp[i - 1][j - 1];
                    dp[i][j] %= MOD;
                }
            }
        }

        return dp[n + k - 1][2 * k];
    }
};