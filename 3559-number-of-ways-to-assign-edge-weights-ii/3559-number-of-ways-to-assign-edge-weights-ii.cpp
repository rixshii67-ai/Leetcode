class Solution {
public:
    static constexpr int MOD = 1e9 + 7;
    static constexpr int LOG = 17; // 2^17 > 1e5

    vector<vector<int>> up;
    vector<int> depth;

    long long modPow(long long a, long long b) {
        long long res = 1;

        while (b) {
            if (b & 1)
                res = res * a % MOD;

            a = a * a % MOD;
            b >>= 1;
        }

        return res;
    }

    void dfs(int node, int parent,
             vector<vector<int>>& adj) {
        up[0][node] = parent;

        for (int nxt : adj[node]) {
            if (nxt == parent) continue;

            depth[nxt] = depth[node] + 1;
            dfs(nxt, node, adj);
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int k = 0; k < LOG; k++) {
            if (diff & (1 << k))
                u = up[k][u];
        }

        if (u == v) return u;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }

        return up[0][u];
    }

    vector<int> assignEdgeWeights(vector<vector<int>>& edges,
                                  vector<vector<int>>& queries) {

        int n = edges.size() + 1;

        vector<vector<int>> adj(n + 1);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        up.assign(LOG, vector<int>(n + 1));
        depth.assign(n + 1, 0);

        dfs(1, 0, adj);

        for (int k = 1; k < LOG; k++) {
            for (int v = 1; v <= n; v++) {
                up[k][v] = up[k - 1][ up[k - 1][v] ];
            }
        }

        vector<int> ans;

        for (auto& q : queries) {
            int u = q[0];
            int v = q[1];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            int a = lca(u, v);

            int dist = depth[u] + depth[v] - 2 * depth[a];

            ans.push_back(modPow(2, dist - 1));
        }

        return ans;
    }
};