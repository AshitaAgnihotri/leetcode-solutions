class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);
        // Build directed graph
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            adj[u].push_back({v, w});
        }
        // dist[node][consecutive count]
        vector<vector<long long>> dist(n, vector<long long>(k + 1, LLONG_MAX));
        // {distance, node, consecutive count}
        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>
        > pq;
        // Starting node has consecutive count = 1
        dist[0][1] = 0;
        pq.push({0, 0, 1});
        while (!pq.empty()) {
            auto [d, node, cnt] = pq.top();
            pq.pop();
            // Ignore outdated states
            if (d != dist[node][cnt]) {
                continue;
            }
            // Destination reached
            if (node == n - 1) {
                return (int)d;
            }
            for (auto [next, weight] : adj[node]) {
                int newCnt;
                if (labels[node] == labels[next]) {
                    newCnt = cnt + 1;
                }
                else {
                    newCnt = 1;
                }
                // Cannot exceed k consecutive characters
                if (newCnt > k) {
                    continue;
                }
                long long newDist = d + weight;
                if (newDist < dist[next][newCnt]) {
                    dist[next][newCnt] = newDist;
                    pq.push({newDist, next, newCnt});
                }
            }
        }
        return -1;
    }
};
