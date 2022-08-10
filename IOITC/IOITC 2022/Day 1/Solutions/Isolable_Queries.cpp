#include <bits/stdc++.h>
using namespace std;

pair<int, int> query(vector<int> S);

// DO NOT CHANGE ANYTHING ABOVE THIS LINE

pair<int, int> query_xx(vector<int> S){
    if(S.size() >= 2) return query(S);
    else return {S[0],S[0]};
}

int n;

int root;
set<pair<int,int> > edges;
int mxd;
int dep[1005];
vector<int> gg[1005];
int mem[1005];
int deg[1005];

void solve(vector<int> v){
    if(v.size() == 1){
        root = v[0];
        mxd = 0;
        dep[root] = 0;
        for(int i = 0; i <= n; i++) gg[i].clear();
        gg[0].push_back(root);
        mem[0] = v[0];
        return;
    }
    auto [l,sm] = query_xx(v);
    vector<int> v0;
    for(auto x:v){
        if(x != l) v0.push_back(x);
    }
    solve(v0);
    int low = 1,high = mxd,mid,res = 0; // height of its parent
    int par = root;
    while(low <= high){
        mid = (low+high)/2;
        vector<int> v1,v2;
        for(int i = 0; i <= mid; i ++){
            for(auto x:gg[i]){
                v1.push_back(x);
                v2.push_back(x);
            }
        }
        v2.push_back(l);
        int p = mem[mid]+l-query_xx(v2).second;
        if(p){
            par = p;
            res = mid;
            low = mid+1;
        }
        else high = mid-1;
    }
    edges.insert({par,l});
    deg[par]++;
    deg[l]++;
    dep[l] = dep[par]+1;
    if(dep[l] > mxd){
        mxd = dep[l];
        mem[dep[l]] = mem[dep[l]-1];
    }
    gg[dep[l]].push_back(l);
    for(int i = dep[l]; i <= mxd; i ++){
        mem[i] += l;
        if(deg[par] == 2) mem[i] -= par;
    }
    // cout << l << " " << par << " ----\n";
    // for(int i = 0; i <= mxd; i ++){
    //     cout << i << " ::: " << mem[i] << "\n";
    // }
}


vector<pair<int, int>> getEdges(int n){
    if(n == 2){
        return {{1,2}};
    }
    edges.clear();
    ::n = n;
    vector<int> v;
    for(int i = 1; i <= n; i ++){
        v.push_back(i);
        deg[i] = 0;
    }
    solve(v);
    vector<pair<int,int>> ans;
    for(auto x:edges){
        ans.push_back(x);
        // cout << x.first << " " << x.second << "\n";
    }
    return ans;
}