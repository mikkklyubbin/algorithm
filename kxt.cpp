struct vec { // radius vector
    double x, y;

    vec(double x_ = 0, double y_ = 0) {
        x = x_;
        y = y_;
    }

    vec(vec a, vec b) { // declaration from 2 polls
        x = b.x - a.x;
        y = b.y - a.y;
    }

    vec operator+(vec b) const {
        return {x + b.x, y + b.y};
    }

    vec operator-(vec b) const {
        return {x - b.x, y - b.y};
    }

    vec operator-() const {
        return {-x, -y};
    }

    double length() const {
        return sqrt(x * x + y * y);
    }

    vec operator*(double k) const { // stretching to k times
        return {x * k, y * k};
    }

    vec operator/(double k) const { // stretching to 1/k times
        return {x / k, y / k};
    }

    double operator*(vec b) const { // scalar product
        return x * b.x + y * b.y;
    }

    double operator%(vec b) const { // vector product
        return x * b.y - b.x * y;
    }

    friend istream &operator>>(istream &in, vec &v) {
        in >> v.x >> v.y;
        return in;
    }

    friend ostream &operator<<(ostream &out, const vec &v) {
        out << v.x << ' ' << v.y;
        return out;
    }

    bool is_poll_in_seg(vec b, vec c) const { // check is this poll in segment bc
        vec c1 = c - b;
        vec d = *this - b;
        double f = (d * c1);
        double q = d.length() * c1.length();
        return fabs(f - q) < pog &&
               (x >= min(b.x, c.x) && x <= max(b.x, c.x) && y >= min(c.y, b.y) && y <= max(c.y, b.y));
    }
};

struct line {
    double a, b, c; // ax + by + c = 0
    line(double a_, double b_, double c_) {
        a = a_;
        b = b_;
        c = c_;
    }

    line(vec aa, vec bb) { // declaration from to polls in line
        a = (bb.y - aa.y);
        b = (aa.x - bb.x);
        c = (bb.x * aa.y - aa.x * bb.y);
    }

    double get_x(double y = 0) const {
        return (-b * y - c) / a;
    }

    double get_y(double x = 0) const {
        return (-a * x - c) / b;
    }

    double distance_from_poll(vec yy) const {
        double te = fabs(a * yy.x + b * yy.y + c);
        double tee = sqrt(a * a + b * b);
        return te / tee;
    }

    vec cross_poll(line t) const {
        double x = (b * t.c - t.b * c) / (a * t.b - t.a * b);
        double y = -(a * t.c - t.a * c) / (a * t.b - t.a * b);
        return {x, y};
    }
};

struct kxt {
    vector<pair<double, ll>> stek;

    void add(ll i) {
        line new_line = {double(b[i]), -1, double(dp[i])};
        while (stek.size() >= 2) {
            ll indb1 = stek.back().second;
            line b1 = {double(b[indb1]), -1, double(dp[indb1])};
            double ch1 = b1.cross_poll(new_line).x;
            if (ch1 >= stek.back().first) {
                break;
            }
            stek.pop_back();
        }
        ll indb1 = stek.back().second;
        line b1 = {double(b[indb1]), -1, double(dp[indb1])};
        stek.push_back({b1.cross_poll(new_line).x, i});
    }

    ll get_ind(ll x) {
        ll l = 0;
        ll r = stek.size();
        while (r - l > 1) {
            ll mid = (r + l) / 2;
            if (stek[mid].first < x) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return stek[l].second;
    }
};
