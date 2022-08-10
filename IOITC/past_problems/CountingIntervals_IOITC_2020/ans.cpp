#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

struct DSU {
	vector<int> p, s, mx, mn;

	void init(int n) {
		p = vector<int>(n);
		mx = vector<int>(n);
		mn = vector<int>(n);
		iota(all(p), 0);
		iota(all(mx), 0);
		iota(all(mn), 0);
		s = vector<int>(n, 1);
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
		mn[b] = min(mn[b], mn[a]);
		mx[b] = max(mx[b], mx[a]);
	}

	bool good(int a) {
		a = get(a);

		return (mx[a] - mn[a] + 1 == s[a]);
	}
};

void solve() {
	int n, m; cin >> n >> m;

	DSU dsu;
	dsu.init(n);

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		a--, b--;
		dsu.unite(a, b);
	}

	set<int> par;

	for (int i = 0; i < n; i++) {
		par.insert(dsu.get(i));
	}
	int ans = 0;
	for (int elt : par) {
		bool ok = dsu.good(elt);
		
	} // we can also merge adj components

	cout << ans << endl;
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