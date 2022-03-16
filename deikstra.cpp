#include <iostream>
#include <vector>
#include <set>
#include <utility>
using namespace std;
struct edge{
    int to;
    int weight;
    bool operator<(const edge &other)const{
      if (weight!=other.weight){
        return weight<other.weight;
      }
      return to<other.to;
    }
};
const int inf =2e9;
int main(){
    int n,m, from,to,weight,start,fin;
    cin>>n>>m;
    cin>>start>>fin;
    vector<vector<edge>> g(n);
    vector<int> p(n,-1);
    for (int i =0 ; i<m;i++){
        cin>>from >>to >>weight;
        from--;
        to--;
        g[from].push_back({to,weight});
        g[to].push_back({from,weight});

    }
    start--;
    fin--;
    vector<int> d(n,inf);
    vector<int> used(n);
    vector<int> ed(n);
    set<edge> st;
    d[start]=0;
    st.insert({start,0});
    while(!st.empty()){
        edge cur =*st.begin();
        int v =cur.to;
        st.erase(st.begin());
        if (d[v]==inf){
            break;
        }

        used[v]=1;
        for (edge next : g[v]){
            if (used[next.to]==0 && (d[next.to]>d[v]+next.weight)){
                auto it =st.find({next.to,d[next.to]});
                if (it!=st.end()){
                    st.erase(it);
                }

                d[next.to]=d[v]+next.weight;
                p[next.to]=v;
                st.insert({next.to,d[next.to]});
            }
        }
        }

    if (d[fin]!=inf){
        int f=fin;
        int h=0;
        while (f!=-1){
            ed[h]=f;
            f=p[f];
            h++;
        }
        cout<<d[fin]<<endl;
        cout<<h<<endl;
        for (int i=h-1; i>-1;i--){
            cout<<ed[i]+1<<" ";
        }
    }
    else{
        cout<<-1;
    }



}