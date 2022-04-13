#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long

vector<vector<int>> adj;
vector<ll int> w;
ll int ans = 0;

void dfs(int u, ll int cur) {
	cur = max(w[u], cur);
	for (auto v : adj[u]) {
		ans = max(cur - w[v], ans);
		dfs(v, cur);
	}
}

void solve() {
	int n; cin >> n;
	adj.resize(n + 1);
	w.resize(n + 1);
	for (int i = 1; i <= n; i++) cin >> w[i];
	int head = -1;
	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		// cout << pl(a) << endl;
		if (a == -1) {
			head = i + 1;
			continue;
		}
		adj[a].push_back(i + 1);
	}
	assert(head > 0);
	// cout << pl(head) << endl;

	dfs(head, w[head]);

	cout << ans << endl;
}

int main() {
	// cin.tie(nullptr);
	// ios::sync_with_stdio(false);

	solve();
	// int t; cin >> t;
	// while (t--) {
	// 	solve();
	// }

	return 0;
}