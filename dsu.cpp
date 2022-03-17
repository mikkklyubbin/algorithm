#include <iostream>
#include <iostream>
#include <stack>
#include <vector>
#include<set>
using namespace std;
const long long inf = 1e18;
struct edge{
    int from;
    int to;
    long long w;
};
struct dsu{
    vector<int> p;
    vector<int> deep;
    dsu(int n){
        p.resize(n);
        deep.resize(n);
        for(int i=0;i<n;i++){
            p[i]=i;
            deep[i]=1;
        }
    }
    int get(int x){
        if (p[x]==x){
            return x;
        }
        return p[x]=get(p[x]);
    }
    void join(int x,int y){
        x=get(x);
        y=get(y);
        if (x==y){
            return;
        }
        if (deep[x]<deep[y]){
            swap(x,y);
        }
        if (deep[x]==deep[y]){
            deep[x]++;
        }
        p[y]=x;
    }
    bool check(int x,int y){
        if (get(x)==get(y)){
            return true;
        }
        else{
            return false;
        }
    }
};
