class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        long long dp = 0;
        vector<long long> last(26, 0);
        for (char c : s) {
            int idx = c - 'a';
            long long newDp = (2 * dp + 1 - last[idx] + MOD) % MOD;
            last[idx] = dp + 1;
            dp = newDp;
        }
        return dp;
    }
};