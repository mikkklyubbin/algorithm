struct koras {
    vector<vector<int>> go = {vector<int>(26, -1)};
    vector<vector<int>> term = {{}};
    vector<int> suf = {0}, supsuf = {0};
    int cur = 0;

    void add(string a, int ind) {
        int v = 0;
        for (auto c: a) {
            if (go[v][c - 'a'] == -1) {
                go.emplace_back(26, -1);
                term.push_back({});
                suf.push_back(0);
                supsuf.push_back(0);
                go[v][c - 'a'] = go.size() - 1;
            }
            v = go[v][c - 'a'];
        }
        term[v].push_back(ind);
    }

    void build() {
        queue<int> que;
        que.push(0);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            if (v == 0) {
                suf[v] = v;
                for (int i = 0; i < 26; i++) {
                    if (go[v][i] == -1) {
                        go[v][i] = 0;
                    } else {
                        suf[go[v][i]] = v;
                        supsuf[go[v][i]] = 0;
                        que.push(go[v][i]);
                    }
                }
            } else {
                for (int i = 0; i < 26; i++) {
                    if (go[v][i] == -1) {
                        go[v][i] = go[suf[v]][i];
                    } else {
                        suf[go[v][i]] = go[suf[v]][i];
                        if (term[suf[go[v][i]]].size() > 0) {
                            supsuf[go[v][i]] = suf[go[v][i]];
                        } else {
                            supsuf[go[v][i]] = supsuf[suf[go[v][i]]];
                        }
                        que.push(go[v][i]);
                    }
                }
            }
        }
    }

    vector<int> move(char c) {
        cur = go[cur][c - 'a'];
        vector<int> ans;
        int v = cur;
        while (v != 0) {
            for (auto el: term[v]) {
                ans.push_back(el);
            }
            v = supsuf[v];
        }
        return ans;
    }
};
