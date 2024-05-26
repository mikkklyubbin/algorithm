#pragma GCC target("avx2")
#pragma GCC optimize("O3")
//#pragma GCC optimize("trapv")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//typedef __int128 vll;
typedef long double ld;

//a

istream &operator>>(istream &in, __int128 &a) {
    long long x;
    in >> x;
    a = x;
    return in;
}

ostream &operator<<(ostream &out, __int128 v) {
    long long g = v;
    out << g;
    return out;
}

template<typename T>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &el: v) {
        in >> el;
    }
    return in;
}

template<typename T>
ostream &operator<<(ostream &out, vector<T> &v) {
    for (auto el: v) {
        out << el << " ";
    }
    return out;
}

//ll const mod = 1e9 + 7;
ll const MOD = 1e6 + 3;
unsigned long milliseconds_since_epoch =
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::milliseconds(1);
mt19937 rd(milliseconds_since_epoch);


// you can edit this to change error rate

ll bin_pow(ll x, ll step, ll n) {
    ll ans = 1;
    while (step != 0){
        if (step % 2){
            ans *= x;
            ans %= n;
        }
        x *= x;
        x %= n;
        step /= 2;
    }
    return ans;
}


bool check_all_steps(ll d, ll a, ll n) {
    ll x = bin_pow(a, d, n);
    if (x == 1) {
        return true;
    }
    while (d != n - 1) {
        if (x == n - 1) {
            return true;
        }
        x *= x;
        x %= n;
        d *= 2;
    }
    return false;
}

bool check(ll n) {
    ll d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    for (ll i = 0; i < 40; i++) {
        ll a = rd() % n;
        if (a != 0 && !check_all_steps(d, a, n)) {
            return false;
        }
    }
    return true;
}

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

ll fun(ll x, ll n) {
    return (x * x + 1) % n;
}

vector<ll> get_dels(ll n) {
    if (n == 1) return {};
    if (check(n)) {
        return {n};
    }
    for (ll j = 2; j <= 100; j++) {
        if (n % j == 0) {
            vector<ll> a = get_dels(n / j);
            a.push_back(j);
            return a;
        }
    }
    ll s = sqrt(n);
    if (s * s == n) {
        vector<ll> a = get_dels(s);
        for (auto el: get_dels(s)) {
            a.push_back(el);
        }
        return a;
    }
    while (true) {
        ll x0 = rd() % n;
        ll x1 = x0;
        for (int g = 3 * sqrt(sqrt(n)); g > -1; g--) {
            x0 = fun(x0, n);
            x1 = fun(fun(x1, n), n);
            ll f = gcd((x1 - x0 + n) % n, n);
            if (f != n && f != 1) {
                vector<ll> a = get_dels(f);
                for (auto el: get_dels(n / f)) {
                    a.push_back(el);
                }
                return a;
            }
        }
    }
}


ll get_solve(ll a, ll b, ll m) {
    for (ll i = 0; i < 100; i++) {
        if (bin_pow(a, i, m) == b) {
            return i;
        }
    }
    ll k = sqrt(m) + 100;
    ll g = bin_pow(a, k, m);
    ll f = 1;
    vector<pair<ll, ll>> had;
    for (ll j = k; j <= m + k; j += k) {
        f *= g;
        f %= m;
        had.emplace_back(f, j);
    }
    std::sort(had.begin(), had.end());
    ll tmp = 1;
    for (ll l = 0; l <= k; l++) {
        auto it = std::lower_bound(had.begin(), had.end(), pair<ll, ll>{(b * tmp) % m, 50 + l});
        if (it->first == (b * tmp) % m && bin_pow(a, it->second - l, m) == b) {
            return it->second - l;
        }
        tmp *= a;
        tmp %= m;
    }
    return -1;
}

vector<ll> dels(map<ll, ll> cnt, ll it) {
    if (cnt[it] == 0) {
        return {1};
    }
    ll g = 1;
    vector<ll> f2;
    vector<ll> f = dels(cnt, cnt.upper_bound(it)->first);
    for (ll i = 0; i <= cnt[it]; i++) {
        for (auto el: f) {
            f2.push_back(el * g);
        }
        g *= it;
    }
    return f2;
}

ll sqrt_of_mod(ll p) {
    if (p == 2) return 1;
    for (int i = 1; i <= p; i++) {
        bool is = true;
        for (int j = 1; j * j <= (p - 1); j++) {
            if ((p - 1) % j == 0) {
                ll k = bin_pow(i, j, p);
                ll k2 = bin_pow(i, (p - 1) / j, p);
                if (k == 1 || (k2 == 1 && j != 1)) {
                    is = false;
                    break;
                }
            }
        }
        if (is) {
            return i;
        }
    }
}

ll for_prost(ll a, ll p) {
    if (a == 0) return 0;
    ll g = sqrt_of_mod(p);
    ll step = get_solve(g, a, p);
    if (step % 2 == 1 || step == -1) {
        return -1;
    }
    return bin_pow(g, step / 2, p);
}


ll for_kprost(ll a, ll p, ll cnt) {
    if (a == 0) return 0;
    ll maxim = bin_pow(p, cnt, 1e18);
    a %= maxim;
    ll d_mnog = 1;
    ll l = 0;
    while (a % p == 0) {
        l++;
        a /= p;
    }
    if (l % 2 == 1) return -1;
    d_mnog = bin_pow(p, l / 2, 1e18);
    ll t = for_prost(a % p, p);
    if (t == -1) {
        return -1;
    }
    if (p == 2) {
        vector<ll> ans(max(6ll, cnt + 1), -1);
        ll our_step = p;
        for (int j = 1; j <= 5; j++) {
            for (int i = 0; i < j * p; i++) {
                if (i * i % our_step == a % our_step) {
                    ans[j] = i;
                }
            }
            our_step *= p;
        }
        if (cnt <= 5) {
            if (ans[cnt] == -1){
                return -1;
            }
            return ans[cnt] * d_mnog % maxim;
        }
        for (ll i = 6; i <= cnt; i++) {
            t = ans[i - 1];
            if (t == -1) {
                return -1;
            }
            ll right = ((a - t * t + our_step) % our_step) / bin_pow(p, i - 1, 1e18);
            right %= p;
            right *= bin_pow(t, p - 2, p);
            right %= p;
            t = (t + right * bin_pow(p, i - 2, 1e18));
            ans[i] = t;
            our_step *= p;
        }
        return t * d_mnog % maxim;
    } else {
        ll our_step = p;
        for (ll i = 2; i <= cnt; i++) {
            ll n_step = our_step * p;
            ll right = ((a - t * t % n_step  + n_step) % n_step) / our_step;
            right %= p;
            right *= bin_pow(2 * t, p - 2, p);
            right %= p;
            t = (t + right * our_step) % n_step;
            our_step = n_step;
        }
        return t * d_mnog % maxim;
    }

}

pair<ll, ll> egcd(ll a, ll b, ll c) {
    if (a == 0) {
        if (c % b != 0) {
            assert(false);
        }
        return {0, c / b};
    }
    auto [y0, x0] = egcd(b % a, a, c);
    ll y = y0;
    ll x = x0 - (b / a) * y;
    return {x, y};
}


ll sqrt_mod(ll a, ll m) {
    if (a == 0) return 0;
    if (m == 1) return 0;
    vector<ll> delim = get_dels(m);
    map<ll, ll> cnt;
    for (auto el: delim) {
        cnt[el]++;
    }
    ll ans = -1;
    ll m1 = -1;
    for (auto el: cnt) {
        ll g = for_kprost(a % bin_pow(el.first, el.second, 1e18), el.first, el.second);
        if (g == -1) {
            return -1;
        }
        if (ans == -1) {
            ans = g;
            m1 = bin_pow(el.first, el.second, 1e18);
        } else {
            ll z = bin_pow(el.first, el.second, 1e18);
            auto [x, y] = egcd(m1, z, 1);
            ll n_m = m1 * z;
            x += n_m;
            x %= n_m;
            y += n_m;
            y %= n_m;
            ll f1 = (ans * z % n_m * y % n_m + g * m1 % n_m * x % n_m) % n_m;
            ans = f1;
            m1 = n_m;
        }
    }
    return ans;
}

void solve() {
    ll a, m;
    a %= m;
    cin >> a >> m;
    ll g1 = sqrt_mod(a, m);
    if (g1 == -1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << g1 << "\n";
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll tt = 1;
    cin >> tt;
    while (tt) {
        solve();
        tt--;
    }
    return 0;
}
