class Solution {
    vector<vector<int>> adj, up;
    vector<int> depth, tin, tout, bit;
    int timer, LOG, N;
    // Fenwick Tree supporting XOR updates and queries
    vector<int> fenwick;
    void updateBIT(int i, int val) {
        for (; i <= N; i += i & -i) {
            fenwick[i] ^= val;
        }
    }
    int queryBIT(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) {
            res ^= fenwick[i];
        }
        return res;
    }
    int getMask(char c) {
        return 1 << (c - 'a');
    }
    // Iterative DFS avoids stack overflow on a chain-shaped tree
    void dfs(int root) {
        vector<array<int, 3>> st;
        st.push_back({root, root, 0});
        while (!st.empty()) {
            auto [u, p, state] = st.back();
            st.pop_back();
            if (state == 0) {
                up[0][u] = p;
                tin[u] = ++timer;
                // Record entry time
                updateBIT(tin[u], bit[u]);
                st.push_back({u, p, 1});
                for (int v : adj[u]) {
                    if (v == p) continue;
                    depth[v] = depth[u] + 1;
                    st.push_back({v, u, 0});
                }
            } else {
                tout[u] = ++timer;
                // Record exit time
                updateBIT(tout[u], bit[u]);
            }
        }
    }
    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int diff = depth[u] - depth[v];
        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j)) {
                u = up[j][u];
            }
        }
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }
        return up[0][u];
    }
public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        bit.resize(n);
        N = 2 * n;
        timer = 0;
        LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }
        fenwick.assign(N + 1, 0);
        up.assign(LOG, vector<int>(n, 0));
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            bit[i] = getMask(s[i]);
        }
        dfs(0);
        // Binary lifting table
        for (int j = 1; j < LOG; j++) {
            for (int u = 0; u < n; u++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
        }
        vector<bool> ans;
        for (string& q : queries) {
            string op;
            int u;
            char c;
            stringstream ss(q);
            ss >> op >> u;
            if (op == "update") {
                ss >> c;
                int newMask = getMask(c);
                int delta = bit[u] ^ newMask;
                if (delta != 0) {
                    updateBIT(tin[u], delta);
                    updateBIT(tout[u], delta);
                    bit[u] = newMask;
                    s[u] = c;
                }
            } else {
                int v;
                ss >> v;
                int w = lca(u, v);
                int prefixU = queryBIT(tin[u]);
                int prefixV = queryBIT(tin[v]);
                int mask = prefixU ^ prefixV ^ bit[w];
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }
        return ans;
    }
};
