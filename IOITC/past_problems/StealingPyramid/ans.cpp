#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

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
	int n; cin >> n;

	vector<int> h(n); for (int i = 0; i < n; i++) cin >> h[i];
	vector<int> f(n); for (int i = 0; i < n; i++) cin >> f[i];
	DSU dsu;
	dsu.init(n);
	for (int i = 0; i < n; i++) {
		if (i + f[i] < n) dsu.unite(i, i + f[i]);
		if (i - f[i] >= 0) dsu.unite(i, i - f[i]); 
	}

	bool ok = 1;

	for (int i = 0; i < n; i++) {
		if (!dsu.same_set(i, h[i] - 1)) ok = 0;
	}

	if (ok) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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
