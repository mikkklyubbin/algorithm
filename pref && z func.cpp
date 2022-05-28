#include <bits/stdc++.h>
#include <cmath>
using namespace std;
vector<int> zf(string s){
    vector<int>zff(s.size());
    zff[0]=s.size();
    int l=0,r=0;
    for (int i=1;i<s.size();++i){
        zff[i]=max(0,min(zff[i-l],r-i+1));
        while(i+zff[i]<s.size() && s[i+zff[i]]==s[zff[i]]){
            zff[i]++;
        }
        if (i+zff[i]-1>=r){
            l=i;
            r=i+zff[i]-1;
        }
    }
    return zff;

}
vector<int> preffun(string s){
    vector<int> pref(s.size());
    pref[0]=0;
    for (int i=1;i<s.size();++i){
        pref[i]=pref[i-1];
        while (pref[i]!=0 && s[i]!=s[pref[i]]){
            pref[i]=pref[pref[i]-1];
        }
        if (s[i]==s[pref[i]]){
            pref[i]++;
        }
    }
    return pref;
}