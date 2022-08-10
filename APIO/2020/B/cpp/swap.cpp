#include "swap.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

const int LOG = 20;
const int inf = 1e9 + 7;

struct DSU { // Sorry UFDS
	int n, m;
	vector<int> p, s, degree, dep;
	vector<bool> swappable;
	vector<int> swap_cost;
	vector<vector<int>> jumpNode, jumpMinSwap, adj;
	int next_node;

	void init(int _n, int _m) {
		n = _n;
		m = _m;

		next_node = n;

		p = vector<int>(n + m + 1); // n leaves and m internal nodes
		iota(all(p), 0);

		degree = vector<int>(n, 0);
		swappable = vector<bool>(n + m + 1, 0);
		swap_cost = vector<int>(n + m + 1, inf);

		jumpNode = vector<vector<int>>(n + m + 1, vector<int>(LOG));
		jumpMinSwap = vector<vector<int>>(n + m + 1, vector<int>(LOG));
	}

	int get(int x) {
		return p[x] == x ? p[x] : get(p[x]); // no path compression
	}

	void unite(int a, int b, int wt) {
		degree[a]++;
		degree[b]++;
		int pa = get(a);
		int pb = get(b);

		if (pa == pb) {
			p[pa] = next_node;

			swappable[next_node] = 1;
			swap_cost[pa] = wt;
			next_node++;
			return;
		}

		bool _swappable = 0;
		if (degree[a] >= 3 || degree[b] >= 3) _swappable = 1;

		p[next_node] = next_node;
		p[pa] = next_node;
		p[pb] = next_node;
		swappable[next_node] = (_swappable | swappable[pa] | swappable[pb]);

		if (swappable[next_node]) swap_cost[next_node] = wt;
		next_node++;
	}

	void init_lca() {
		adj.resize(n + m + 1);
		dep.resize(n + m + 1);

		for (int i = 0; i < n + m + 1; i++) {
			adj[p[i]].push_back(i);

			jumpNode[i][0] = p[i]; // parent of the ith node
			jumpMinSwap[i][0] = swap_cost[i];
		}

		for (int i = 1; i < LOG; i++) {
			for (int j = 0; j < n + m + 1; j++) {
				jumpNode[j][i] = jumpNode[jumpNode[j][i - 1]][i - 1];
				jumpMinSwap[j][i] = min(jumpMinSwap[j][i - 1], jumpMinSwap[jumpNode[j][i - 1]][i - 1]);
			}
		}

		init_dfs(next_node - 1, 0);
	}

	pair<int, int> kth(int u, int k) {
		int pow = LOG - 1;
		int res = inf;

		while (k > 0) {
			while (k < (1 << pow)) pow--;
			res = min(res, jumpMinSwap[u][pow]);
			u = jumpNode[u][pow];
			k -= (1 << pow);
		}

		return make_pair(u, res);
	}

	void init_dfs(int u, int d) {
		dep[u] = d;

		for (int v : adj[u]) if (v != u) init_dfs(v, d + 1);
	}

	int lca(int a, int b) {
		if (dep[a] < dep[b]) swap(a, b);
		a = kth(a, dep[a] - dep[b]).first;

		if (a == b) return a;

		int pow = LOG - 1;

		while (pow >= 0) {
			if (jumpNode[a][pow] != jumpNode[b][pow]) {
				a = jumpNode[a][pow];
				b = jumpNode[b][pow];
			}

			pow--;
		}
		assert(jumpNode[a][0] == jumpNode[b][0]);
		return jumpNode[a][0];
	}

	int when_swappable(int a, int b) {
		int l = lca(a, b);

		return kth(l, dep[l] + 1).second;
	}
};

int n, m;
vector<vector<pair<int, int>>> adj;
vector<pair<int, pair<int, int>>> edges;
DSU dsu;

void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) {
	n = N;
	m = M;
	adj.resize(n);

	for (int i = 0; i < m; i++) {
		adj[U[i]].emplace_back(V[i], W[i]);
		adj[V[i]].emplace_back(U[i], W[i]);
		edges.emplace_back(W[i], make_pair(U[i], V[i]));
	}

	sort(all(edges));
	dsu.init(n, m);

	for (auto edge : edges) {
		dsu.unite(edge.second.first, edge.second.second, edge.first);
	}

	dsu.init_lca();
}

int getMinimumFuelCapacity(int x, int y) {
	int res = dsu.when_swappable(x, y);

	return res >= inf ? -1 : res;
}
