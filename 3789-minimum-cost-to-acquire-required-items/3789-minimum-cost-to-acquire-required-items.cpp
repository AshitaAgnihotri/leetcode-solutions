class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        
        long long mn = min(need1, need2);
        long long mx = max(need1, need2);

        // Case 1: Buy individual items
        long long ans1 = 1LL * need1 * cost1 + 1LL * need2 * cost2;

        // Case 2: Buy only combined items
        long long ans2 = 1LL * mx * costBoth;

        // Case 3: Buy combined items for common needs
        // and individual items for remaining needs
        long long ans3 = 1LL * mn * costBoth + 1LL * (need1 - mn) * cost1 + 1LL * (need2 - mn) * cost2;

        return min({ans1, ans2, ans3});
    }
};
