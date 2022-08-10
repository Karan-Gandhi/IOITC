#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

struct DSU {
	vector<int> p, s;
	int components;

	void init(int n) {
		p = vector<int>(n, 0);
		iota(all(p), 0);
		s = vector<int>(n, 1);
		components = n;
	}

	int get(int x) {
		return p[x] = p[x] == x ? x : get(p[x]);
	}

	void unite(int a, int b) {
		a = get(a);
		b = get(b);

		if (a == b) return;

		if (s[a] > s[b]) swap(a, b);
		p[a] = b;
		s[b] += s[a];
		components--;
	}

	bool same_set(int a, int b) {
		return get(a) == get(b);
	}
};

vector<vector<int>> adj, dfsTree;
vector<int> dp, dep;
vector<bool> vis, badPoint;
vector<int> component, _par;
vector<pair<int, int>> edges;
DSU dsu;

void dfs(int u, int par, int d = 0) {
	vis[u] = 1;
	dep[u] = d;

	for (int v : adj[u]) {
		if (v == par) continue;

		if (!vis[v]) {
			dfs(v, u, d + 1);
			dp[u] += dp[v];
		} else {
			if (dep[v] < dep[u]) dp[u]++;
			else dp[u]--;
		}
	}

	if (u != par && dp[u] != 0) {
		dsu.unite(u, par); // 
	} else if (u != par) {
		edges.emplace_back(par, u);
	}
}

void dfs2(int u, int d = 0) {
	cout << pl(u) << endl;
	dep[u] = d;

	for (int v : dfsTree[u]) {
		dfs2(v, d + 1);
	}
}

void solve() {
	// dfsTree
	// if c is acc of a or c is acc of b and c is not acc of lca(a, b) then backedge over c must be >= 1
	// else if c == lca(a, b) there should be 2 back edges one from a side and one from b side
	// rather doing this which is tedious we can decompose the graph into nodes
	// we can find bcc using dfstree

	int n, m, q; cin >> n >> m >> q;

	adj.resize(n);
	dfsTree.resize(n);
	dp.resize(n);
	dep.resize(n);
	vis.resize(n);
	component.resize(n);
	dsu.init(n);
	_par.resize(n);
	badPoint.resize(n);

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		a--, b--;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(0, 0);

	for (int i = 0; i < n; i++) {
		component[i] = dsu.get(i);
	}

	int root = dsu.get(0);

	for (auto [u, v] : edges) {
		dfsTree[component[u]].push_back(component[v]);
		_par[component[v]] = component[u];
	}

	const int LOG = 20;
	vector<vector<int>> jump(n, vector<int>(LOG));

	for (int i = 0; i < n; i++) {
		jump[i][0] = _par[i];
	}

	for (int i = 1; i < LOG; i++) {
		for (int j = 0; j < n; j++) {
			jump[j][i] = jump[jump[j][i - 1]][i - 1];
		}
	}

	auto kth = [&](int u, int k) {
		int pow = LOG - 1;
		while (k > 0) {
			while (k < (1 << pow)) pow--;
			u = jump[u][pow];
			k -= (1 << pow);
		}

		return u;
	};

	dfs2(root);

	auto lca = [&](int a, int b) {
		if (dep[a] < dep[b]) swap(a, b);
		a = kth(a, dep[a] - dep[b]);
		if (a == b) return a;
		int pow = LOG - 1;

		while (pow >= 0) {
			if (jump[a][pow] != jump[b][pow]) {
				a = jump[a][pow];
				b = jump[b][pow];
			}

			pow--;
		}

		assert(jump[a][0] == jump[b][0]);
		return jump[a][0];
	};

	while (q--) {
		int a, b, c; cin >> a >> b >> c;
		a--, b--, c--;

		if (dp[c] != 0) {
			cout << "YES" << endl;
			continue;
		}

		if (component[a] == component[b] && component[a] != component[c]) {
			cout << "YES" << endl;
		} else if (component[a] == component[b] && component[a] == component[c]) {
			// just handle this case
			cout << "YES" << endl;
		} else {
			int L1 = lca(component[a], component[c]);
			int L2 = lca(component[b], component[c]);
			int L3 = lca(component[a], component[b]);

			cout << pl(L1) << pl(L2) << pl(L3) << pl(a) << pl(b) << pl(c) << endl;
			cout << pl(component[a]) << pl(component[b]) << pl(component[c]) << endl;

			if ((L1 == L3 && L2 == component[c]) || (L2 == L3 && (L1 == component[c]))) {
				cout << "NO" << endl;
			}  else {
				cout << "YES" << endl;
			}
		}
	}
}

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--)
		solve();
}