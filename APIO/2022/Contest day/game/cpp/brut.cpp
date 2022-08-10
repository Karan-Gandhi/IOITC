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


// vector<set<int>> from, to;
// vector<int> from;
vector<vector<int>> adj, rev;
vector<bool> cycle;
vector<bool> vis;
int n, k;

int to = -1;
int from = -1;

void dfs1(int u) {
	if (vis[u]) return;
	vis[u] = 1;
	// cout << pl(u) << endl;
	// cout << pl(adj[u]) << endl;
	// cout << pl(vis) << endl;
	if (u < k) {
		if (to == -1) to = u;
		to = min(to, u);
		vis[u] = 0;
		return;
	}

	for (int v : adj[u]) {
		dfs1(v);
	}

	vis[u] = 0;
}

void dfs2(int u) {
	if (vis[u]) return;
	vis[u] = 1;

	if (u < k) {
		if (from == -1) from = u;
		from = max(from, u);
		vis[u] = 0;
		return;
	}

	for (int v : rev[u]) {
		dfs2(v);
	}

	vis[u] = 0;
}

void init(int _n, int _k) {
	n = _n;
	k = _k;

	adj.resize(n);
	rev.resize(n);
	vis.resize(n);
	cycle.resize(n);
}

int add_teleporter(int u, int v) {
	// cout << pl(u) << pl(v) << endl;
	adj[u].push_back(v);
	rev[v].push_back(u);
	// check for the least edge v goes to and the least edge u goes to
	to = -1;
	from = -1;
	// fill(all(vis), 0);
	dfs1(v);
	// fill(all(vis), 0);
	dfs2(u);

	// cout << pl(to) << pl(from) << endl;

	if (to == -1 || from == -1) return 0;

	return to <= from;
}
