struct li_chao_tree {
    struct line {
        ll k, b;
    };
    struct node {
        line n_line;
        node *left_son = nullptr;
        node *right_son = nullptr;
    };
    vector<ll> x;
    node *root;
    ll cnt = 0;

    explicit li_chao_tree(vector<ll> x_) {
        x = std::move(x_);
    }

    void add(node *v, line a, ll l, ll r) {
        ll m = (r + l) / 2;
        if (a.k * x[m] + a.b > v->n_line.k * x[m] + v->n_line.b) {
            swap(a, v->n_line);
        }
        if (r - l == 1) {
            return;
        }
        if (a.k > v->n_line.k) {
            if (v->right_son == nullptr) {
                v->right_son = new node({a});
                return;
            }
            add(v->right_son, a, m + 1, r);
        } else {
            if (v->left_son == nullptr) {
                v->left_son = new node({a});
                return;
            }
            add(v->left_son, a, l, m);
        }
    }

    void add(line a) {
        if (cnt == 0) {
            cnt = 1;
            root = new node({a});
            return;
        }
        add(root, a, 0, x.size());
    }

    ll get(ll x_for_s, node *v, ll l, ll r) {
        ll m = (r + l) / 2;
        ll f = v->n_line.k * x_for_s + v->n_line.b;
        if (x_for_s < x[m]) {
            if (v->left_son == nullptr) {
                return f;
            }
            return max(f, get(x_for_s, v->left_son, l, m));
        } else {
            if (v->right_son == nullptr) {
                return f;
            }
            return max(f, get(x_for_s, v->right_son, m + 1, r));
        }
    }

    ll get(ll x_for_s){
        return get(x_for_s, root, 0, x.size());
    }
};
