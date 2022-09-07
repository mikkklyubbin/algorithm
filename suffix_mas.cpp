struct suffix_mas {
    int n;
    int max_c;
    vector<int> p;
    vector<int> s;

    struct p_s {
        int ind_s;
        int ind_mid;

    };

    void sup_sort(vector<p_s> &sortabel, bool is) const {
        vector<int> sizes(n);
        vector<p_s> ans(n);
        for (int i = 0; i < n; i++) {
            if (is) {
                sizes[s[sortabel[i].ind_s]]++;
            } else {
                sizes[s[sortabel[i].ind_mid]]++;
            }
        }
        for (int i = 1; i < n; i++) {
            sizes[i] += sizes[i - 1];
        }
        for (int i = 0; i < n; i++) {
            if (is) {
                if (s[sortabel[i].ind_s] == 0) {
                    ans[0] = sortabel[i];
                } else {
                    ans[sizes[s[sortabel[i].ind_s] - 1]] = sortabel[i];
                    sizes[s[sortabel[i].ind_s] - 1]++;
                }
            } else {
                if (s[sortabel[i].ind_mid] == 0) {
                    ans[0] = sortabel[i];
                } else {
                    ans[sizes[s[sortabel[i].ind_mid] - 1]] = sortabel[i];
                    sizes[s[sortabel[i].ind_mid] - 1]++;
                }
            }
        }
        sortabel = ans;
    }

    void update_p(const vector<p_s> &sorted) {
        for (int i = 0; i < n; i++) {
            p[i] = sorted[i].ind_s;
        }
    }

    [[nodiscard]] vector<int> update_s(const vector<p_s> &sorted) {
        vector<int> ans(n, 0);
        int ind = 0;
        for (int i = 1; i < n; i++) {
            if (s[sorted[i].ind_s] != s[sorted[i - 1].ind_s] || s[sorted[i].ind_mid] != s[sorted[i - 1].ind_mid]) {
                ind++;
            }
            ans[sorted[i].ind_s] = ind;
        }
        max_c = ind;
        return ans;
    }

    suffix_mas(string start_string) {
        start_string += ('a' - 1);
        n = start_string.size();
        p.resize(n);
        s.resize(n, 0);
        vector<vector<int>> for_s(30);
        for (int i = 0; i < n; i++) {
            for_s[start_string[i] - ('a' - 1)].push_back(i);
        }
        vector<int> sorted;
        for (const auto &el: for_s) {
            for (auto el2: el) {
                sorted.push_back(el2);
            }
        }
        for (int i = 0; i < n; i++) {
            p[i] = sorted[i];
        }
        int ind = 0;
        for (int i = 1; i < n; i++) {
            if (start_string[sorted[i]] != start_string[sorted[i - 1]]) {
                ind++;
            }
            s[sorted[i]] = ind;
        }
        max_c = ind;
        int len = 1;
        vector<p_s> temp(n);
        while (len < n && max_c < n) {
            for (int i = 0; i < n; i++) {
                temp[i] = {i, (i + len) % n};
            }
            sup_sort(temp, false);
            sup_sort(temp, true);
            update_p(temp);
            s = update_s(temp);
            len *= 2;
        }
    }


};
