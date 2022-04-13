#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

struct DSU {
	vector<ll int> p, s, m;
	ll int components = 0;

	void init(ll int n) {
		p = vector<ll int>(n);
		s = vector<ll int>(n, 1);
		m = vector<ll int>(n, 0);
		iota(all(p), 0);
		components = 1;
	}

	ll int get(ll int x) {
		return p[x] = (p[x] == x ? x : get(p[x])); // no path compression + lca
	}

	void unite(ll int a, ll int b) {
		a = get(a);
		b = get(b);
		if (a == b) {
			return;
		}

		if (s[a] > s[b]) swap(a, b);
		// cout << pl(a) << pl(b) << endl;
		p[a] = b;
		s[b] += s[a];
		components = max(components, s[b]);
	}

	bool same_set(ll int a, ll int b) {
		return get(a) == get(b);
	}

	ll int size(int x) {
		return s[get(x)];
	}
};

void solve() {
	ll int n, m; cin >> n >> m;
	ll int t; cin >> t;

	vector<vector<ll int>> arr(n, vector<ll int>(m));
	for (ll int i = 0; i < n; i++) for (ll int j = 0; j < m; j++) cin >> arr[i][j];

	DSU dsu; dsu.init(n * m + 1);

	function<ll int(ll int, ll int)> idx = [&](ll int i, ll int j) -> ll int {
		return m * i + (j + 1);
	};

	vector<pair<ll int, pair<ll int, ll int>>> edges;
	for (ll int i = 0; i < n; i++) {
		for (ll int j = 0; j < m; j++) {
			if (i != 0) {
				edges.emplace_back(abs(arr[i][j] - arr[i - 1][j]), make_pair(idx(i, j), idx(i - 1, j)));
			}

			if (j != 0) {
				edges.emplace_back(abs(arr[i][j] - arr[i][j - 1]), make_pair(idx(i, j), idx(i, j - 1)));
			}

			if (i != n - 1) {
				edges.emplace_back(abs(arr[i][j] - arr[i + 1][j]), make_pair(idx(i, j), idx(i + 1, j)));
			}

			if (j != m - 1) {
				edges.emplace_back(abs(arr[i][j] - arr[i][j + 1]), make_pair(idx(i, j), idx(i, j + 1)));
			}
		}
	}

	sort(all(edges));

	ll int ans = 0;
	ll int cur_i = 0;
	ll int cur = 0;

	for (ll int i = 0; i < n; i++) {
		for (ll int j = 0; j < m; j++) {
			ll int s; cin >> s;
			if (s == 1) {
				while (cur_i < (ll int) edges.size() && dsu.size(idx(i, j)) < t) {
					dsu.unite(edges[cur_i].second.first, edges[cur_i].second.second);
					cur = max(cur, edges[cur_i].first);
					cur_i++;
				}
				ans += cur;
			}
		}
	}

	cout << ans << endl;
}

int main() {
	// what if I store the first and last occurence of each element
	// find the number of elements whose first and last occurence is between [range_low, range_hi]
	// freopen("skilevel.out", "w", stdout);
	// freopen("skilevel.in", "r", stdin);
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}