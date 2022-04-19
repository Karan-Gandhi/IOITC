#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

vector<vector<int>> adj;
vector<int> vals;
vector<bool> vis;
vector<int> dp;

void dfs(int u) {
	if (vis[u]) return;
	vis[u] = 1;
	for (int v : adj[u]) dfs(v);
}

void solve() {
	int n, m; cin >> n >> m;
	adj.resize(n);
	vector<pair<int, int>> arr;
	vals.resize(n);
	vis.resize(n);
	dp.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> vals[i];

		arr.emplace_back(vals[i], i);
	}

	sort(all(arr));

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;

		a--, b--;
		adj[a].push_back(b);
	}

	int ans = 0;

	for (int i = n - 1; i >= 0; i--) {
		int node = arr[i].second;
		fill(all(vis), 0);
		dfs(node);
		dp[node] = 1;

		for (int j = 0; j < n; j++) {
			if (j == node || !vis[j]) continue;
			dp[node] = max(dp[node], dp[j] + (vals[j] > vals[node]));
		}

		ans = max(ans, dp[node]);
	}

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