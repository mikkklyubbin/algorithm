#include <iostream>
#include <fstream>
#include<set>
#include <vector>
#include <iomanip>
using namespace std;
const long long inf = 1e10;
const long long mod=1e9+7;
vector<vector<int>> sparse;
vector<int> logs;
int n;
void init_logs(){
    logs.resize(n+1);
    logs[1]=0;
    for (int i=2;i<=n;i++){
        logs[i]=logs[i/2]+1;
    }
}
int get_max(int ll,int rr){
    int l=min(ll,rr);
    int r=max(ll,rr);
    int k=logs[r-l+1];
    return min(sparse[k][l],sparse[k][r-(1<<k)+1]);
}
int main(){
    int m;
    cin>>n>>m;
    init_logs();
    sparse.resize(logs[n]+1,vector<int>(n));
    cin>>sparse[0][0];
    for (int i =1;i<n;i++){
        sparse[0][i]=(23*sparse[0][i-1]+21563)%16714589;
    }
    for (int k=1;k<=logs[n];k++){
        for (int i=0;i+(1<<(k-1))<n;i++){
            sparse[k][i]=min(sparse[k-1][i],sparse[k-1][i+(1<<(k-1))]);
        }
    }
    int l,r,templ,temr;
    cin>>l>>r;
    int ans=get_max(l-1,r-1);
    for (int i=0;i<m-1;i++){
        l=((17*l+751+ans+2*(i+1))%n)+1;
        r=((13*r+593+ans+5*(i+1))%n)+1;
        ans=get_max(l-1,r-1);
    }
    cout<<l<<" "<<r<<" "<<ans;
    return 0;
}