struct graph {
    vector<vector<int>> g;
    vector<int> res, used;
    int size;

    graph(int n, int other) {
        size = n;
        g.resize(n);
        res.resize(other, -1);
        used.resize(n, -1);
    }

    bool dfs(int v, int timer) {
        if (used[v] == timer) return false;
        used[v] = timer;
        for (auto u: g[v]) {
            if (res[u] == -1) {
                res[u] = v;
                return true;
            }
        }
        for (auto u: g[v]) {
            if (dfs(res[u], timer)) {
                res[u] = v;
                return true;
            }
        }
        return false;
    }

    void get_parsochi() {
        for (int i = 0; i < size; i++) {
            dfs(i, i);
        }
    }

    void add(int u, int v) {
        g[u].push_back(v);
    }
};
