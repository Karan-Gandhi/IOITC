#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pl(var) " [" << #var << ": " << (var) << "] "

ll int inf = 1e16;
ll int mod = 1e9 + 7;

struct DSU {
	vector<int> p, s;

	void init(int n) {
		p = vector<int>(n);
		s = vector<int>(n, 1);
		iota(all(p), 0);
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
	}

	int size(int c) {
		return s[get(c)];
	}

	bool same_set(int a, int b) {
		return get(a) == get(b);
	}
};

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<int>> ids(n);

	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		ids[i] = vector<int>(k);
		for (int j = 0; j < k; j++) {
			cin >> ids[i][j];
		}
	}

	function <bool(int, int)> edge_exists = [&] (int i, int j) -> bool {
		unordered_map<int, bool> vis;
		int equal = 0;
		for (auto a : ids[i]) vis[a] = 1;
		for (auto b : ids[j]) equal += (vis[b]);
		return equal >= m;
	};

	DSU dsu;
	dsu.init(n);

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			// check if i and j is equal
			if (dsu.same_set(i, j)) continue;
			if (edge_exists(i, j)) {
				dsu.unite(i, j);
				if (dsu.size(0) == n) break;
			}
		}
		if (dsu.size(0) == n) break;
	}

	cout << dsu.size(0) << endl;
}

int main() {
	solve();

	return 0;
}