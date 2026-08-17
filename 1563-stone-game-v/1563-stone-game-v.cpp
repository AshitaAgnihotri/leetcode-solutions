class Solution {
public:
int dp[501][501];
    vector<int> pre;
    int solve(vector<int>& a, int i, int j) {
        if (i >= j)
            return 0;
        if (dp[i][j] != -1)
            return dp[i][j];
        int ans = 0;
        for (int k = i; k < j; k++) {
            int left = pre[k + 1] - pre[i];
            int right = pre[j + 1] - pre[k + 1];
            if (left < right) {
                ans = max(ans, left + solve(a, i, k));
            }
            else if (left > right) {
                ans = max(ans, right + solve(a, k + 1, j));
            }
            else {
                ans = max(ans, left + max(solve(a, i, k), solve(a, k + 1, j)));
            }
        }
        return dp[i][j] = ans;
    }
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        pre.resize(n + 1, 0);
        for (int i = 0; i < n; i++)
            pre[i + 1] = pre[i] + stoneValue[i];
        memset(dp, -1, sizeof(dp));
        return solve(stoneValue, 0, n - 1);
    }
};