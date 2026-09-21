class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);
        for (int num : nums) {
            vector<long long> next(k, 0);
            next[num % k]++;
            for (int r = 0; r < k; r++) {
                if (dp[r] > 0) {
                    int newR = (r * (num % k)) % k;
                    next[newR] += dp[r];
                }
            }
            dp = next;
            for (int r = 0; r < k; r++) {
                ans[r] += dp[r];
            }
        }
        return ans;
    }
};