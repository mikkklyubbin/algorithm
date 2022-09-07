struct tree {
    vector<vector<int>> g;
    vector<int> c;
    vector<int> sizes;
    vector<bool> used;

    explicit tree(int n) {
        g.resize(n);
        c.resize(n);
        sizes.resize(n);
        used.resize(n, false);
    }

    int size() {
        return g.size();
    }

    void add(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void get_deeps(int u, int p, int d) {
        int size_of_my = 0;
        for (auto el: g[u]) {
            if (!used[el] && el != p) {
                get_deeps(el, u, d + 1);
                size_of_my += sizes[el];
            }
        }
        sizes[u] = size_of_my + 1;
    }
};

struct centroid_tree {
    tree decomposion = tree(0);
    tree for_decomposion = tree(0);
    vector<int> parent;

    int get_centroid(int u) {
        for_decomposion.get_deeps(u, -1, 0);
        return get_centroid(u, -1, for_decomposion.sizes[u]);
    }

    int get_centroid(int u, int p, int n) {
        int max_ver = 0;
        int ind = -1;
        for (auto el: for_decomposion.g[u]) {
            if (el != p && !for_decomposion.used[el]) {
                max_ver = max(max_ver, for_decomposion.sizes[el]);
                if (max_ver == for_decomposion.sizes[el]) {
                    ind = el;
                }
            }
        }
        if (max_ver <= n / 2) {
            for_decomposion.used[u] = true;
            for (auto el: for_decomposion.g[u]) {
                if (!for_decomposion.used[el]) {
                    int x = get_centroid(el);
                    parent[x] = u;
                    decomposion.add(u, x);
                }
            }
            return u;
        }
        return get_centroid(ind, u, n);
    }

    explicit centroid_tree(tree b) {
        decomposion = tree(b.size());
        for_decomposion = b;
        parent.resize(b.size(), -1);
        get_centroid(0);
    }
};
