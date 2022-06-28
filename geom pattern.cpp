
#include <bits/stdc++.h>
using namespace std;
double pog = 1e-6; // you can edit this to change error rate

struct vec { // radius vector
    double x, y;

    vec(double x_ = 0, double y_ = 0) {
        x = x_;
        y = y_;
    }

    vec(vec a, vec b) { // declaration from 2 points
        x = b.x - a.x;
        y = b.y - a.y;
    }

    vec operator+(vec b) const {
        return {x + b.x, y + b.y};
    }
    vec operator-(vec b) const{
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

    friend ostream &operator<<(ostream &out, const vec& v) {
        out << v.x << ' ' << v.y;
        return out;
    }
    bool is_point_in_seg(vec b, vec c) const{ // check is this point in segment bc
        vec c1 = c - b;
        vec d = *this - b;
        double  f = (d * c1);
        double q = d.length() * c1.length();
        return fabs(f - q) < pog && (x >= min(b.x, c.x) && x <= max(b.x, c.x) && y >= min(c.y, b.y) && y <= max(c.y, b.y));
    }
};

struct polygon{
    vector<vec> points;
    unsigned long long number_of_points;

    polygon(const vector<vec> &vectors){
        points=vectors;
        number_of_points=points.size();
    }

    double area(){
        double area = 0;
        for (int i = 0;i < number_of_points;i++){
            vec a = points[i];
            vec b = points[(i + 1) % points.size()] - a;
            area += (a % b);
        }
        return area / 2;
    }

    bool is_Convex(){
        bool temp = true;
        for (int i = 0;i < number_of_points;i++){
            vec a = vec(points[(i - 1 + points.size()) % points.size()], points[i]);
            vec b = vec(points[i], points[(i + 1) % points.size()]);
            if (a % b > 0){
                temp = false;
            }
        }
        return temp;
    }

    polygon Convex_hull(){ // create the smallest convex hull
        vec p = points[0];
        for (int i = 1;i < points.size();i++){
            if (points[i].y < p.y || points[i].y == p.y && points[i].x > p.x){
                p = points[i];
            }
        }
        sort(points.begin(), points.end(), [p](const vec& v1,const vec& v2) -> bool{
            double prod = (v1 - p) % (v2 - p);
            if (fabs(prod) < pog){
                return (v1 - p).length() < (v2 - p).length();
            }
            return prod > 0;
        });
        vector<vec> hull;
        for(vec cur : points){
            while(hull.size() >= 2){
                vec a = cur - hull.back();
                vec b = hull.back() - hull[hull.size() - 2];
                if(b % a > 0) break;
                hull.pop_back();
            }
            hull.push_back(cur);
        }
        return {hull};
    }

    bool checkpoint(vec p){ // check is point p in polygon
        double s = 0;
        for (int i = 0;i < number_of_points;i++){
            vec a = points[(i - 1 + number_of_points) % number_of_points];
            vec b = points[i];
            if (p.is_point_in_seg(b, a) || (p.x == b.x && p.y == b.y)) return true;
            a = p - a;
            b = p - b;
            s += atan2((a % b),(a * b));
        }
        return (fabs(fabs(s) - 2 * M_PI) < 1e-4);
    }
};
struct line{
    double a, b, c; // ax + by + c = 0
    line (double a_,double b_,double c_){
        a=a_;
        b=b_;
        c=c_;
    }
    line(vec aa, vec bb){ // declaration from to points in line
        a = (bb.y - aa.y);
        b = (aa.x - bb.x);
        c = (bb.x * aa.y - aa.x * bb.y);
    }
    double get_x(double y = 0) const{
        return (-b * y -c) / a;
    }
    double get_y(double x = 0) const{
        return (-a * x - c) / b;
    }
    double distance_from_point(vec yy) const{
        double te = fabs(a * yy.x + b * yy.y + c);
        double tee = sqrt(a * a + b * b);
        return te / tee;
    }
    vec cross_point(line t) const{
        double x = (b * t.c - t.b * c) / (a * t.b - t.a * b);
        double y = -(a * t.c - t.a * c) / (a * t.b - t.a * b);
        return {x, y};
    }
};
struct circle{
    double r;
    double x0;
    double y0;
    circle (int r1, vec cennn){
        r = r1;
        x0 = cennn.x;
        y0 = cennn.y;
    }
    pair<int,pair<vec,vec>> touch_points(vec b) const{
        vec cen = {x0, y0};
        vec d = b - cen; // vector of line form centre of circle to point
        double n = sqrt(d.length() * d.length() - r * r);
        vec om = d * ((r * r) / (d.length() * d.length()));
        vec o = om + cen;
        vec var1 = {-om.y, om.x};
        vec var2 = {om.y, -om.x};
        vec oa = var1 * (n / r) + o;
        vec ob = var2 * (n / r) + o;
        if (d.length() < r){
            return {0, {{0, 0}, {0, 0}}};
        }
        if (d.length() - r < pog){
            return {1, {oa, ob}};
        }
        return {2,{oa,ob}};
    }
    pair<int,pair<vec,vec>> points_of_line_cross(line b) const{
        vec cen={x0,y0};
        double d=b.distance_from_point(cen);
        vec h(b.a,b.b);
        vec cenpr=h+cen;
        line ss(cen,cenpr);
        vec o(b.cross_point(ss));
        vec popram(-b.b,b.a);
        vec popram2(b.b,-b.a);
        double ll=sqrt(r*r-d*d);
        vec oa=popram*(ll/popram.length());
        vec aa = o+popram*(ll/popram.length());
        vec bb = o+popram2*(ll/popram2.length());
        if (d<r){
            return {2,{aa,bb}};
        }
        else if (d-r<=pog){
            return {1,{aa,bb}};
        }
        return {0,{aa,bb}};
    }
    pair<int,pair<vec,vec>> circleper(circle b){
        circle temp(r,{0,0});
        circle temp2(b.r,{b.x0-x0,b.y0-y0});
        line f={-2*temp2.x0,-2*temp2.y0,temp2.x0*temp2.x0+temp2.y0*temp2.y0-temp2.r*temp2.r+temp.r*temp.r};
        if (fabs(f.c)<pog){
            return {-1,{{0,0},{0,0}}};
        }
        else{
            pair<int,pair<vec,vec>> c=temp.points_of_line_cross(f);
            vec cen ={x0,y0};
            pair<int,pair<vec,vec>> ans={c.first,{c.second.first+cen,c.second.second+cen}};
            return ans;
        }
    }
};
