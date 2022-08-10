#include "race.h"
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v);
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }


vector<vector<pair<int, int>>> adj;
vector<vector<int>> dp;
// multiset<int> distances;
int k;
int ans = -1;

void dfs(int u, int par) {
    // cout << pl(u) << endl;
    for (auto [v, wt] : adj[u]) {
        if (v == par) continue;
        // cout << pl(v) << pl(wt) << endl;
        dfs(v, u);

        if (wt <= k) dp[u][wt] = 1;
        for (int i = wt + 1; i <= k; i++) {
            if (dp[u][i] != -1) dp[u][i] = min(dp[u][i], ((dp[v][i - wt] == -1) ? dp[u][i] : (dp[v][i - wt] + 1)));
            else dp[u][i] = dp[v][i - wt] + (dp[v][i - wt] != -1 ? 1 : 0);
        }

        // cout << pl(dp[u][k]) << endl;

        if (ans != -1) ans = min(ans, dp[u][k] == -1 ? ans : dp[u][k]);
        else ans = dp[u][k];
    }
}

void dfs1(int u, int par) {
    // for (int i = 0; i <= k; i++) {
    //     ans = min(ans, dp[u][i] + dp[u][k - i]);
    // }

    // go through all the children's dp 
    
    vector<vector<int>> pref, suff;
    pref = suff = vector<vector<int>>(1 + int(adj[u].size()), vector<int>(k + 1, -1));

    for (int j = 1; j <= adj[u].size(); j++) {
    // for (auto [v, wt] : adj[u]) {
        int v = adj[u][j - 1].first;
        int wt = adj[u][j - 1].second;
        if (v == par) continue;

        if (wt <= k) pref[j][wt] = 1;
     
    	for (int i = wt + 1; i <= k; i++) {
            // if (i - wt < 0) continue;
            // cout << pl(pref[j]) << endl;
            // cout << pl(i) << pl(wt) << pl(i - wt) << pl(dp[v][i - wt]) << endl;
            if (pref[j - 1][i] != -1) pref[j][i] = min(pref[j - 1][i - wt], dp[v][i - wt] + (dp[v][i - wt] != -1 ? 1 : 0));
            else pref[j][i] = dp[v][i - wt] + (dp[v][i - wt] != -1 ? 1 : 0);
        }
    }

    // cout << pl(u) << pref << endl;

    for (int j = int(adj[u].size()) - 1; j >= 0; j--) {
    // for (auto [v, wt] : adj[u]) {
        int v = adj[u][j].first;
        int wt = adj[u][j].second;
        if (v == par) continue;

        if (wt <= k) suff[j][wt] = 1;
     
    	for (int i = wt + 1; i <= k; i++) {
            // if (i - wt < 0) continue;
            // cout << pl(pref[j]) << endl;
            // cout << pl(i) << pl(wt) << pl(i - wt) << pl(dp[v][i - wt]) << endl;
            if (suff[j + 1][i] != -1) suff[j][i] = min(suff[j + 1][i - wt], dp[v][i - wt] + (dp[v][i - wt] != -1 ? 1 : 0));
            else suff[j][i] = dp[v][i - wt] + (dp[v][i - wt] != -1 ? 1 : 0);
        }
    }
    // cout << pl(u) << suff << endl;

    for (int i = 0; i < adj[u].size(); i++) {
    	for (int j = 0; j <= k; j++) {
    		if (pref[i][k - j] == -1 && suff[i + 1][k - j] == -1) continue;
    		// int one = min(pref[i][j], suff[i + 1][k - j]);
    		// int two = min()
    		int best = -1;

    		if (pref[i][k - j] != -1) {
    			if (best == -1) best = pref[i][k - j];
    			else best = min(best, pref[i][k - j]);
    		}

    		if (suff[i + 1][k - j] != -1) {
    			if (best == -1) best = suff[i + 1][k - j];
    			else best = min(best, suff[i + 1][k - j]);
    		}
    		assert(best != -1);
    		ans = min(ans, dp[adj[u][i].first][j] + best);
    		// if (ans != -1) ans = min(ans, pref[i][j] + suff[i + 1][k - j]);
    		// else ans = pref[i][j] + suff[i + 1][k - j];
    	}
    }

    for (auto [v, wt] : adj[u]) {
    	if (v == par) continue;
    	dfs1(v, u);
    }
}

int best_path(int n, int _k, int edges[][2], int weight[]) {
    adj = vector<vector<pair<int, int>>>(n);
    k = _k;
    // ans = n - 1;
    dp = vector<vector<int>>(n, vector<int>(k + 1, -1));

    for (int i = 0; i < n - 1; i++) {
        adj[edges[i][0]].emplace_back(edges[i][1], weight[i]);
        adj[edges[i][1]].emplace_back(edges[i][0], weight[i]);
    }
    dfs(0, 0);
    dfs1(0, 0);
    // cout << pl(dp[0][3]) << endl;

    return ans;
}

