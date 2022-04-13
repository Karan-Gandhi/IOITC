#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

struct DSU {
	vector<int> p, s;
	int components = 0;

	void init(int n) {
		p = vector<int>(n);
		s = vector<int>(n, 1);
		iota(all(p), 0);
		components = n;
	}

	int get(int x) {
		return p[x] = (p[x] == x ? p[x] : get(p[x]));
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

ll int cost(ll int a, ll int b) {
	return (2019201913 * a + 2019201949 * b) % 2019201997;
}

void solve() {
	int n, k; cin >> n >> k;

	vector<pair<ll int, pair<int, int>>> edges;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			edges.emplace_back(cost(j, i), make_pair(i, j));
		}
	}

	sort(all(edges));

	DSU dsu;
	dsu.init(n + 1);
	ll int ans = 0;

	for (auto [w, edge] : edges) {
		if (dsu.components == k + 1 && !dsu.same_set(edge.first, edge.second)) {
			ans = w;
			break;
		};
		dsu.unite(edge.first, edge.second);
	}

	assert(dsu.components == k + 1);

	// for (int i = 0; i < edges.size(); i++) {
	// 	cout << edges[i].first << endl;
	// }

	// for (int i = 1; i <= n; i++) {
	// 	cout << dsu.p[i] << endl;
	// }

	cout << ans << endl;
}

int main() {
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// int t; cin >> t;
	// while (t--)
		solve();

	return 0;
}