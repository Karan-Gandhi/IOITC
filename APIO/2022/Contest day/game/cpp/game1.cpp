#include "game.h"
#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

int n, k;

// vector<vector<int>> adj;
// vector<vector<int>> rev;
// vector<int> from;
// vector<int> to;
// vector<bool> vis;

vector<int> adj[1000 + 10], rev[1000 + 10];
int from[1000 + 10], to[1000 + 10];
bool vis[1000 + 10];
bool connected[1000 + 10];
bool rev_connected[1000 + 10];

int dfs1(int u) { // min index that u can go to 
	if (vis[u]) {
		return -1;
	}
	vis[u] = 1;

	if (u < k) {
		vis[u] = 0;
		return u;
	}

	for (int v : adj[u]) {
		// if (!connected[v]) continue;
		int res = dfs1(v);

		if (res == -1) continue;
		if (to[u] == -1) to[u] = res;
		to[u] = min(to[u], res);
	}

	vis[u] = 0;
	return to[u];
}

int dfs2(int u) {
	if (vis[u]) {
		return -1;
	}
	vis[u] = 1;

	if (u < k) {
		vis[u] = 0;
		return u;
	}

	for (int v : rev[u]) {
		// if (!rev_connected[v]) continue;
		int res = dfs2(v);

		if (res == -1) continue;
		if (from[u] == -1) from[u] = res;
		from[u] = max(from[u], res);
	}

	vis[u] = 0;
	return from[u];
}

void init(int _n, int _k) {
	n = _n;
	k = _k;

	// adj.resize(n);
	// rev.resize(n);
	// from.resize(n);
	// to.resize(n);
	// vis.resize(n);

	// fill(all(from), -1);
	// fill(all(to), -1);
	// fill(all(vis), 0);
	memset(from, -1, sizeof from);
	memset(to, -1, sizeof to);
	memset(vis, 0, sizeof vis);
	memset(connected, 0, sizeof vis);
	memset(rev_connected, 0, sizeof vis);

	for (int i = 0; i < k; i++) {
		connected[i] = 1;
		rev_connected[i] = 1;
	}
}

int add_teleporter(int u, int v) {
	adj[u].push_back(v);
	rev[v].push_back(u);

	// connected[u] = connected[u] | connected[v];
	// rev_connected[v] = rev_connected[v] | connected[v];

	if (to[v] <= from[u] && to[v] != -1 && from[u] != -1) return 1;

	int to = dfs1(v);
	int from = dfs2(u);

	// if (to != -1) {
	// 	// adj[v].clear();
	// 	// adj[v].push_back(to);
	// 	// rev[to].push_back(v);
	// }

	// if (from != -1) {
	// 	// rev[u].clear();
	// 	// rev[u].push_back(from);
	// 	// adj[from].push_back(u);
	// }

	if (to == -1 || from == -1) return 0;
	return to <= from;
}
