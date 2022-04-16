#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

ll int inf = 1e16;

struct DSU { // Sorry UFDS
	vector<int> p, s;
	int components;

	void init(int n) {
		p = vector<int>(n);
		iota(all(p), 0);
		s = vector<int>(n, 1);
		components = n;
	}

	int get(int x) {
		return p[x] = (p[x] == x ? x : get(p[x]));
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

void solve() {
	int n, m; cin >> n >> m;
	int k; cin >> k;
	vector<tuple<ll int, int,int>> edges(m), remaining;
	vector<ll int> final_edges;
	
	vector<int> leafs(k);
	vector<bool> is_leaf(n, 0);
	for (int i = 0; i < k; i++) {
		cin >> leafs[i];
		leafs[i]--;
		is_leaf[leafs[i]] = 1;
	}

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		a--, b--;
		ll int w; cin >> w;

		edges[i] = make_tuple(w, a, b);
	}

	if (n == 2) {
		// choose the edge with the min weight
		ll int ans = inf;
		for (auto i : edges) {
			ans = min(ans, get<0>(i));
		}
		cout << ans << endl;
		return;
	}

	sort(all(edges));

	// all the leaf should have a degree of 1
	DSU dsu;
	dsu.init(n);
	int ptr = 0;

	while (dsu.components > 1 && ptr < (int)edges.size()) {
		tuple<ll int, int, int> edge = edges[ptr++];
		if (dsu.same_set(get<1>(edge), get<2>(edge))) continue;

		int a = get<1>(edge);
		int b = get<2>(edge);
		if (is_leaf[a] && is_leaf[b]) continue;
		if (is_leaf[a] || is_leaf[b]) {
			remaining.push_back(edge);
			continue;
		}

		dsu.unite(a, b);
		final_edges.push_back(get<0>(edge));
	}

	// for (int a : final_edges) cout << pl(a) << endl;
	// for (auto a : remaining) cout << pl(get<0>(a)) << endl;

	for (auto edge : remaining) {
		int a = get<1>(edge), b = get<2>(edge);

		if (is_leaf[b]) swap(a, b);

		if (dsu.s[dsu.get(a)] > 1) continue; // a is already linked
		// cout << pl(a) << pl(b) << endl;
		dsu.unite(a, b);
		final_edges.push_back(get<0>(edge)); 
	}


	// for (int i : final_edges) {
	// 	cout << pl(i) << endl;
	// }

	assert(int(final_edges.size()) == n - 1);
	ll int ans = 0;
	for (ll int i : final_edges) {
		ans += i;
	}
	cout << ans << endl;
}

int main() {
	// freopen("cbarn2.in", "r", stdin);
	// freopen("cbarn2.out", "w", stdout);

	// ios::sync_with_stdio(false);
	// cin.tie(nullptr);

	ll int T = 1;
	// cin >> T;
	while (T--)
		solve();
}