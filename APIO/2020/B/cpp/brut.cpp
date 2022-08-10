#include "swap.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
 
const int MAXN = 3e5 + 123;
const int INF = 1e9 + 177013;
vector<int> edg[MAXN];
int depth[MAXN];
int timer = 0;
int rt[MAXN];
int crt[MAXN];
int vcnt = 0;
int n = 0;
int deg[MAXN];
bitset<MAXN> swp;
 
void dfs(int v) {
    //tin[v] = timer++;
    if (depth[rt[v]] - depth[crt[rt[v]]] == depth[crt[rt[v]]] - depth[crt[crt[rt[v]]]]) {
        crt[v] = crt[crt[rt[v]]];
    } else {
        crt[v] = rt[v];
    }
    for (auto u : edg[v]) {
        if (u == rt[v])
            continue;
        depth[u] = depth[v] + 1;
        dfs(u);
    }
    //tout[v] = timer;
}
 
int gst(int i) {
    if (rt[i] == i)
        return i;
    return rt[i] = gst(rt[i]);
}
 
void unite(int i, int j) {
    swp[vcnt] = (++deg[i] >= 3) | (++deg[j] >= 3);
    i = gst(i);
    j = gst(j);
    edg[vcnt].push_back(i);
    rt[i] = vcnt;
    if (i != j) {
        swp[vcnt] = swp[vcnt] | swp[j] | swp[i];
        edg[vcnt].push_back(j);
        rt[j] = vcnt;
    } else {
        swp[vcnt] = 1;
    }
    ++vcnt;
}
 
int get_up(int v, int d) {
    int ans = 0;
    while (depth[v] > d) {
        if (depth[crt[v]] >= d) {
            ans = max(ans, crt[v]);
            v = crt[v];
        } else {
            ans = max(ans, rt[v]);
            v = rt[v];
        }
    }
    return v;
}
 
int lca(int v, int u) {
    pair<int, int> ans(0, 0);
    if (depth[u] > depth[v]) {
        u = get_up(u, depth[v]);
    }
    if (depth[u] < depth[v]) {
        v = get_up(v, depth[u]);
    }
    while (v != u) {
        if (crt[v] == crt[u]) {
            v = rt[v];
            u = rt[u];
        } else {
            v = crt[v];
            u = crt[u];
        }
    }
    return v;
}
 
vector<int> cmprw;
 
void init(int N, int m, vector<int> U, vector<int> V, vector<int> W) {
    n = N;
    vector<pair<int, pair<int, int>>> edg_weight(m);
    for (int i = 0; i < m; ++i) {
        edg_weight[i] = {W[i], {U[i], V[i]}};
        cmprw.push_back(W[i]);
    }
    sort(edg_weight.begin(), edg_weight.end());
    sort(cmprw.begin(), cmprw.end());
    for (int i = 0; i < n + m + 8; ++i)
        rt[i] = i;
    vcnt = n;
    for (auto [w, e] : edg_weight) {
        unite(e.first, e.second);
    }
    for (int i = 0; i < vcnt; ++i) {
        for (auto u : edg[i])
            rt[u] = i;
    }
    for (int i = 0; i < vcnt; ++i) {
        if (rt[i] == i) {
            crt[i] = i;
            dfs(vcnt - 1);
        }
    }
    //for (int i = 0; i < vcnt; ++i) {
        //cout << rt[i] << ' ' << crt[i] << ' ' << swp[i] << endl;
    //}
}
 
int getMinimumFuelCapacity(int X, int Y) {
    int t = lca(X, Y);
    while (!swp[t]) {
        if (rt[t] == t)
            return -1;
        if (swp[crt[t]])
            t = rt[t];
        else
            t = crt[t];
    }
    return cmprw[t - n];
}