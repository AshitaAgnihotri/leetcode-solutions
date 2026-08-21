class Solution {
public:
    using ll = long long;
    long long gcdll(long long a, long long b) {
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();
        vector<pair<ll, int>> subsets;
        for (int mask = 1; mask < (1 << n); mask++) {
            ll l = 1;
            bool ok = true;
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) {
                    ll g = gcdll(l, (ll)coins[i]);
                    if (l > (ll)2e18 / (coins[i] / g)) {
                        ok = false;
                        break;
                    }
                    l = l / g * coins[i];
                }
            }
            if (ok)
                subsets.push_back({l, __builtin_popcount(mask)});
        }
        auto count = [&](ll x) {
            ll res = 0;
            for (auto &[l, bits] : subsets) {
                if (l > x) continue;
                if (bits & 1)
                    res += x / l;
                else
                    res -= x / l;
            }
            return res;
        };
        ll lo = 1, hi = 2e11;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (count(mid) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo;
    }
};