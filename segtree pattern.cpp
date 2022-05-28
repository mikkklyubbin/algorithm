#include <bits/stdc++.h>
#include <cmath>
using namespace std;
const long long inf =1e10;
const long long mod=1000000007;
struct segtree{
    long long NEUTRAL=0;
    long long No_op=LLONG_MIN;
    struct node{
        long long mult;
        long long sum;
    };
    long long op_modif(long long a,long long b,long long len){
        if (b==No_op) return a;
        return b*len;
    }
    long long op_ans(long long a,long long b){
        return a+b;
    }
    vector<node> tree;
    int size;
    void init(int n){
        size=1;
        while (size<n){
            size*=2;
        }
        tree.resize(2*size-1,{0,0});
    }
    void propogate(int v,int l,int r){
        if (tree[v].mult==NEUTRAL) return ;
        if (r-l==1) return;
        long long m=(r-l)/2;
        tree[2*v+1].mult=op_modif(tree[2*v+1].mult,tree[v].mult,1);
        tree[2*v+1].sum=op_modif(tree[2*v+1].sum,tree[v].mult,m);
        tree[2*v+2].mult=op_modif(tree[2*v+2].mult,tree[v].mult,1);
        tree[2*v+2].sum=op_modif(tree[2*v+2].sum,tree[v].mult,m);
        tree[v].mult=No_op;
    }
    void build(int v,int l,int r){
        if (r-l==1){
            tree[v]={1,1};
        }else {
            int mid = (l + r) / 2;
            build(2 * v + 1, l, mid);
            build(2 * v + 2, mid, r);
            tree[v]={1, op_ans(tree[2*v+1].sum,tree[2*v+2].sum)};
        }
    }
    long long sumseg2(int v,int lseg,int rseg,int l,int r){
        propogate(v,l,r);
        if (rseg<=l || lseg>=r){
            return NEUTRAL;
        }
        if (rseg>=r && lseg<=l){
            return tree[v].sum;
        }

        int mid=(l+r)/2;
        long long m1=sumseg2(2*v+1,lseg,rseg,l,mid);
        long long m2=sumseg2(2*v+2,lseg,rseg,mid,r);
        long long res=op_ans(m1,m2);
        return res;
    }
    long long sumseg2(int lseg,int rseg){
        return sumseg2(0,lseg,rseg,0,size);
    }

    void sumseg(int v,int lseg,int rseg,int l,int r,long long x){
        propogate(v,l,r);
        if (rseg<=l || lseg>=r){
            return;
        }
        if (rseg>=r && lseg<=l){
            tree[v].mult= op_modif(tree[v].mult,x,1);
            tree[v].sum=op_modif(tree[v].sum,x,r-l);
            return;
        }

        int mid=(l+r)/2;
        sumseg(2*v+1,lseg,rseg,l,mid,x);
        sumseg(2*v+2,lseg,rseg,mid,r,x);
        tree[v].sum=op_ans(tree[2*v+1].sum,tree[2*v+2].sum);

    }
    void sumseg(int lseg,int rseg,long long x){
        sumseg(0,lseg,rseg,0,size,x);
    }
};



int main() {
    int n,m,x;
    cin>>n>>m;
    segtree a;
    a.init(n);
    for (int i=0;i<m;i++){
        int p1,p2,p3;
        cin>>p1>>p2>>p3;
        if (p1==2){
            cout<<a.sumseg2(p2,p3)<<endl;
        }
        else{
            cin>>x;
            a.sumseg(p2,p3,x);
        }
    }
    return 0;
}
