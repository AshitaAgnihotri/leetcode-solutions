class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = s.size();
        vector<vector<int>> g(n);
        vector<vector<int>> st(26);
        vector<int> ans(n, 1);
        for (int i = 1; i < n; i++) {
            g[parent[i]].push_back(i);
        }
        auto dfs = [&](auto&& dfs, int u, int p) -> void {
            int c = s[u] - 'a';
            st[c].push_back(u);
            for (int v : g[u]) {
                dfs(dfs, v, u);
            }
            int target = p;
            if (st[c].size() > 1) {
                target = st[c][st[c].size() - 2];
            }
            if (target != -1) {
                ans[target] += ans[u];
            }
            st[c].pop_back();
        };
        dfs(dfs, 0, -1);
        return ans;
    }
};