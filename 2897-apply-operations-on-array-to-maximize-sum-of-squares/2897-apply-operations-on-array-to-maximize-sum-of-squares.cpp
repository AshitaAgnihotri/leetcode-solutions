
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1e9 + 7;
        vector<int> bits(31, 0);
        for (int num : nums) {
            for (int i = 0; i < 31; i++) {
                if (num & (1 << i)) {
                    bits[i]++;
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < k; i++) {
            long long num = 0;
            for (int j = 30; j >= 0; j--) {
                if (bits[j] > 0) {
                    num |= (1LL << j);
                    bits[j]--;
                }
            }
            ans = (ans + num * num) % MOD;
        }
        return ans;
    }
};
