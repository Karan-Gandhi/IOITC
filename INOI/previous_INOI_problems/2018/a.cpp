#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long
#define inf 1e16

struct DSU {
	vector<int> p;
	vector<int> s;
	vector<int> w;

	void init(int n) {
		p = vector<int>(n);
		iota(all(p), 0);
		s = vector<int>(n, 1);
		w = vector<int>(n, 0);
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
		w[b] += w[a];
	}
};

void solve() {
	int n, m, k; cin >> n >> m >> k;
	DSU dsu;
	dsu.init(n);
	vector<pair<int, int>> edges;
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		// dsu.unite(a, b);
		edges.emplace_back(a, b);
	}
	for (int i = 0; i < n; i++) {
		cin >> dsu.w[i];
	}

	for (auto a : edges) dsu.unite(a.first, a.second);

	// find the number of distinct sets

	vector<bool> done(n, 0);
	vector<int> distinct;
	for (int i = 0; i < n; i++) {
		// if (get(a))
		int par = dsu.get(i);
		if (done[par]) continue;
		done[par] = 1;
		distinct.push_back(dsu.w[par]);
	}

	if (distinct.size() < k) {
		cout << -1 << endl;
		return;
	}

	sort(all(distinct));

	n = distinct.size();
	int hi = n - 1; int lo = 0;
	// int month = 0;
	ll int ans = 0;
	for (int month = 0; month < k; month++) {
		assert(hi >= lo);
		if (month % 2 == 0) {
			// choose max
			ans += distinct[hi];
			hi--;
		} else {
			// choose min
			ans += distinct[lo];
			lo++;
		}
	}

	cout << ans << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	// solve();
	int t; cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}