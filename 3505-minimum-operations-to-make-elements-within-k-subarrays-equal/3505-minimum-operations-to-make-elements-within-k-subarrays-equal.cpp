
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        multiset<int> left, right;

        long long sumLeft = 0, sumRight = 0;

        // Maintain the correct sizes of both multisets
        auto balance = [&]() {

            int target = (x + 1) / 2;

            while ((int)left.size() > target) {
                int val = *left.rbegin();

                left.erase(prev(left.end()));
                sumLeft -= val;

                right.insert(val);
                sumRight += val;
            }

            while ((int)left.size() < target && !right.empty()) {
                int val = *right.begin();

                right.erase(right.begin());
                sumRight -= val;

                left.insert(val);
                sumLeft += val;
            }
        };

        // Insert an element
        auto add = [&](int val) {

            if (left.empty() || val <= *left.rbegin()) {
                left.insert(val);
                sumLeft += val;
            }
            else {
                right.insert(val);
                sumRight += val;
            }

            balance();
        };

        // Remove an element
        auto remove = [&](int val) {
            auto it = left.find(val);
            if (it != left.end()) {
                left.erase(it);
                sumLeft -= val;
            }
            else {
                it = right.find(val);
                right.erase(it);
                sumRight -= val;
            }
            balance();
        };
        // Cost of making the current window equal
        auto getCost = [&]() -> long long {
            long long median = *left.rbegin();
            return median * left.size() - sumLeft
                 + sumRight - median * right.size();
        };
        // Calculate cost for every window of size x
        vector<long long> cost;
        for (int i = 0; i < n; i++) {
            add(nums[i]);
            if (i >= x) {
                remove(nums[i - x]);
            }
            if (i >= x - 1) {
                cost.push_back(getCost());
            }
        }
        // Dynamic Programming
        const long long INF = 1e18;
        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);
        for (int t = 1; t <= k; t++) {
            fill(curr.begin(), curr.end(), INF);
            for (int i = 1; i <= n; i++) {
                // Option 1: Skip current position
                curr[i] = curr[i - 1];
                // Option 2: Take a window of size x
                if (i >= x) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }
            prev = curr;
        }
        return prev[n];
    }
};
