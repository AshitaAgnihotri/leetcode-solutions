class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        const long long BASE = 19;
        const long long MOD = 1e9 + 7;
        vector<long long> power(n + 1, 1);
        for (int i = 1; i <= n; i++)
            power[i] = (power[i - 1] * BASE) % MOD;
        auto check = [&](int len) {
            unordered_map<long long, int> freq;
            long long hash = 0;
            for (int i = 0; i < len; i++) {
                hash = (hash * BASE + nums[i]) % MOD;
            }
            freq[hash]++;
            for (int i = len; i < n; i++) {
                hash = (hash - nums[i - len] * power[len - 1] % MOD + MOD) % MOD;
                hash = (hash * BASE + nums[i]) % MOD;
                freq[hash]++;
            }
            for (auto &p : freq) {
                if (p.second == 1)
                    return true;
            }
            return false;
        };
        int left = 1, right = n, ans = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (check(mid)) {
                ans = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return ans;
    }
};