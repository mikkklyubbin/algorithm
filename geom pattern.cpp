#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>
using namespace std;
double pog=1e-6;

struct vec {
    double x, y;

    vec(double x_ = 0, double y_ = 0) {
        x = x_;
        y = y_;
    }
    // по двум точкам находить вектор соединяющий их, AB = B - A
    vec(vec a, vec b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    vec operator+(vec b) {
        return vec(x + b.x, y + b.y);
    }
    vec operator-(vec b) const{
        return vec(x - b.x, y - b.y);
    }
    vec operator-() {
        return vec(-x, -y);
    }

    double length() const {
        return sqrt(x * x + y * y);
    }

    vec operator*(double k) {
        return vec(x * k, y * k);
    }

    vec operator/(double k) {
        return vec(x / k, y / k);
    }

    int operator*(vec b) { // скалярное
        return x*b.x+y*b.y;
    }

    int operator%(vec b) { // векторное
        return x*b.y-b.x*y;
    }

    friend istream &operator>>(istream &in, vec &v) {
        in >> v.x >> v.y;
        return in;
    }

    friend ostream &operator<<(ostream &out, const vec& v) {
        out << v.x << ' ' << v.y;
        return out;
    }

};
bool isinn_ot(vec a,vec b,vec c){
    vec c1=c-b;
    vec d=a-b;
    double  f=(d*c1);
    double q=d.length()*c1.length();
    return fabs(f-q)<pog && (a.x>=min(b.x,c.x) && a.x<=max(b.x,c.x)&&a.y>=min(c.y,b.y) && a.y<=max(c.y,b.y));
}
struct polygon{
    vector<vec> points;
    int n;
    polygon(const vector<vec> &vectors){
        points=vectors;
        n=points.size();
    }
    double area(){
        double aree=0;
        for (int i=0;i<points.size();i++){
            vec a=points[i];
            vec b = points[(i+1)%points.size()]-a;
            aree+=(a%b);
        }
        return aree/2;
    }
    bool isConvex(){
        bool temp=true;
        for (int i=0;i<points.size();i++){
            vec a= vec(points[(i-1+points.size())%points.size()],points[i]);
            vec b=vec(points[i],points[(i+1)%points.size()]);

            if (a%b>0){
                temp= false;
            }
        }
        return temp;
    }
    polygon Convexhul(){
        vec p = points[0];
        for (int i=1;i<points.size();i++){
            if (points[i].y<p.y || points[i].y==p.y && points[i].x>p.x){
                p=points[i];
            }
        }
        sort(points.begin(),points.end(),[p](const vec& v1,const vec& v2) -> bool{
            int prod = (v1-p)%(v2-p);
            if (prod==0){
                return (v1-p).length()<(v2-p).length();
            }
            return prod>0;
        });
        vector<vec> hull;
        for(vec cur: points){
            while(hull.size()>=2){
                vec a = cur-hull.back();
                vec b= hull.back()-hull[hull.size()-2];
                if(b%a>0){
                    break;
                }
                hull.pop_back();
            }
            hull.push_back(cur);
        }
        return {hull};
    }
    bool checkpoint(vec p){
        double s=0;
        for (int i=0;i<n;i++){
            vec a=points[(i-1+n)%n];
            vec b=points[i];
            if (isinn_ot(p,b,a) || (p.x==b.x && p.y==b.y)){
                return true;
            }
            a=p-a;
            b=p-b;

            s+= atan2((a%b),(a*b));


        }
        return (fabs(fabs(s)-2*M_PI)<1e-4);
    }
};
struct line{
    double a,b,c;
    line(double a_=0,double b_=0,double c_=0){
        a=a_;
        b=b_;
        c=c_;
    }
    line(vec aa, vec bb){
        a=(bb.y-aa.y);
        b=(aa.x-bb.x);
        c=(bb.x*aa.y-aa.x*bb.y);
    }
    float getx(float y=0){
        return (-b*y-c)/a;
    }
    float gety(float x=0){
        return (-a*x-c)/b;
    }
    double lenwithtli(vec yy){
        double te=fabs(a*yy.x+b*yy.y+c);
        double tee=sqrt(a*a+b*b);
        return (te/tee);
    }
    double perx(line t){
        double x=(b*t.c-t.b*c)/(a*t.b-t.a*b);
        return x;
    }
    double pery(line t){
        double y=-(a*t.c-t.a*c)/(a*t.b-t.a*b);
        return y;
    }
};
struct circle{
    int r;
    double x0;
    double y0;
    circle (int r1,vec cennn){
        r=r1;
        x0=cennn.x;
        y0=cennn.y;
    }
    pair<int,pair<vec,vec>> casispoint(vec b){
        vec cen={x0,y0};

        vec d=b-cen;
        double n=sqrt(d.length()*d.length()-r*r);
        vec om =d*((r*r)/(d.length()*d.length()));
        vec o=om+cen;
        vec var1={-om.y,om.x};
        vec var2={om.y,-om.x};
        vec oa=var1*(n/r)+o;

        vec ob=var2*(n/r)+o;
        if (d.length()<r){
            return {0,{{0,0},{0,0}}};
        }
        if (d.length()-r<pog){
            return {1,{oa,ob}};
        }
        return {2,{oa,ob}};
    }
    pair<int,pair<vec,vec>> lineper(line b){
        vec cen={x0,y0};
        double d=b.lenwithtli(cen);
        vec h(b.a,b.b);
        vec cenpr=h+cen;
        line ss(cen,cenpr);
        vec o(b.perx(ss),b.pery(ss));
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
        line f(-2*temp2.x0,-2*temp2.y0,temp2.x0*temp2.x0+temp2.y0*temp2.y0-temp2.r*temp2.r+temp.r*temp.r);
        if (fabs(f.c)<pog){
            return {-1,{{0,0},{0,0}}};
        }
        else{
            pair<int,pair<vec,vec>> c=temp.lineper(f);
            vec cen ={x0,y0};
            pair<int,pair<vec,vec>> ans={c.first,{c.second.first+cen,c.second.second+cen}};
            return ans;
        }
    }
};

int main() {

}