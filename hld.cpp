struct segmetree {
    vector<int> tree;
    int size = 1;

    segmetree(int n) {
        while (size < n) {
            size *= 2;
        }
        tree.resize(2 * size - 1, 0);
    }

    void update(int v, int l, int r, int x, int ind) {
        if (r - l == 1) {
            tree[v] = x;
            return;
        }
        int mid = (r + l) / 2;
        if (ind < mid) {
            update(2 * v + 1, l, mid, x, ind);
        } else {
            update(2 * v + 2, mid, r, x, ind);
        }
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void update(int ind, int x) {
        update(0, 0, size, x, ind);
    }

    int get(int v, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        if (ql >= r || qr <= l) {
            return -1;
        }
        int mid = (r + l) / 2;
        return max(get(2 * v + 1, l, mid, ql, qr), get(2 * v + 2, mid, r, ql, qr));
    }

    int get(int ql, int qr) {
        return get(0, 0, size, ql, qr);
    }
};

struct bin_up {
    vector<vector<int>> bin_up;
    vector<int> logs;
    int n;

    void init_logs() {
        logs.resize(n + 1);
        logs[1] = 0;
        for (int i = 2; i <= n; i++) {
            logs[i] = logs[i / 2] + 1;
        }
    }

    void init(vector<int> &a) {
        n = a.size();
        init_logs();
        bin_up.resize(logs[n] + 1, vector<int>(n));
        bin_up[0] = a;
        for (ll k = 1; k <= logs[n]; k++) {
            for (ll i = 0; i < n; i++) {
                ll parent = bin_up[k - 1][i];
                bin_up[k][i] = bin_up[k - 1][parent];
            }
        }
    }

    ll get(ll i, ll k) {
        return bin_up[k][i];
    }
};

vector<int> sizes;

struct hld {
    int n;
    vector<vector<int>> g;
    vector<int> ind_of_roads, tin, tout, head_of_roads, for_bins;
    bin_up waq;
    int t = 0;
    segmetree mach = segmetree(0);

    static bool comp(const int a, const int b) {
        if (sizes[a] == sizes[b]) {
            return a > b;
        }
        return sizes[a] > sizes[b];
    }

    hld(int n_) {
        n = n_;
        g.resize(n);
        ind_of_roads.resize(n, -1);
        tin.resize(n);
        tout.resize(n);
        sizes.resize(n, 1);
        for_bins.resize(n, 0);
        mach = segmetree(2 * n);
    }

    void add(int v, int u) {
        g[v].push_back(u);
        g[u].push_back(v);
    }

    void dfs(int v, int p = 0) {
        for_bins[v] = p;
        for (auto el: g[v]) {
            if (el != p) {
                dfs(el, v);
                sizes[v] += sizes[el];
            }
        }
    }

    void dfs_eler(int v, int p = -1) {
        tin[v] = t++;
        bool is = true;
        for (auto el: g[v]) {
            if (el != p) {
                dfs_eler(el, v);
                if (is) {
                    ind_of_roads[v] = ind_of_roads[el];
                    head_of_roads[ind_of_roads[el]] = v;
                    is = false;
                }
            }
        }
        if (ind_of_roads[v] == -1) {
            head_of_roads.push_back(v);
            ind_of_roads[v] = head_of_roads.size() - 1;
        }
        tout[v] = t++;
    }

    void get_eler() {
        dfs(0);
        for (int i = 0; i < n; i++) {
            std::sort(g[i].begin(), g[i].end(), comp);
        }
        dfs_eler(0);
        waq.init(for_bins);
    }

    void set(int v, int x) {
        mach.update(tin[v], x);
    }

    bool acs(int pred, int det) {
        return tin[pred] <= tin[det] && tin[det] <= tout[pred];
    }

    ll get_LCA(int u, int v) {
        if (acs(u, v)) return u;
        if (acs(v, u)) return v;
        for (int i = waq.bin_up.size() - 1; i > -1; i--) {
            if (!acs(waq.bin_up[i][v], u)) {
                v = waq.bin_up[i][v];
            }
        }
        return waq.bin_up[0][v];
    }

    int get(int v1, int u1) {
        int maxim = 0;
        int LCA = get_LCA(v1, u1);
        int ind = ind_of_roads[v1];
        int head = head_of_roads[ind];
        while (!acs(head, LCA)) {
            maxim = max(maxim, mach.get(tin[head], tin[v1] + 1));
            v1 = for_bins[head];
            ind = ind_of_roads[v1];
            head = head_of_roads[ind];
        }
        ind = ind_of_roads[u1];
        head = head_of_roads[ind];
        while (!acs(head, LCA)) {
            maxim = max(maxim, mach.get(tin[head], tin[u1] + 1));
            u1 = for_bins[head];
            ind = ind_of_roads[u1];
            head = head_of_roads[ind];
        }
        maxim = max(maxim, mach.get(tin[LCA], tin[u1] + 1));
        maxim = max(maxim, mach.get(tin[LCA], tin[v1] + 1));
        return maxim;

    }
};
