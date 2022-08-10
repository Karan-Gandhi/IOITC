#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

void solve() {
	// dp[u] = 1
	// dp[u] *= dp[v] + 1;
	int n; cin >> n;
	vector<ll int> dp(n);
	vector<vector<int>> adj(n);
	// dp[all other nodes] remains the same
	// dp[prev root] /= dp[cur root] + 1
	// dp[cur root] *= dp[prev root] + 1

	int m; cin >> m;

	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b;
		a--, b--;
		
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	function<void(int, int)> dfs1 = [&](int u, int par) {
		dp[u] = 1;

		for (int v : adj[u]) {
			if (v == par) continue;

			dfs1(v, u);
			dp[u] *= dp[v] + 1ll;
		}
	};
	dfs1(0, 0);
	vector<ll int> ans(n);
	function<void(int, int)> dfs2 = [&](int u, int par) {
		if (u == par) {
			ans[u] = dp[u] % m;

			for (int v : adj[u]) {
				dfs2(v, u);
			}
			return;
		}

		dp[par] /= dp[u] + 1;
		dp[u] *= dp[par] + 1;
		ans[u] = dp[u] % m;
		for (int v : adj[u]) {
			if (v == par) continue;
			dfs2(v, u);
		}

		dp[u] /= dp[par] + 1;
		dp[par] *= dp[u] + 1;
	};
	dfs2(0, 0);

	for (int i : ans) cout << i << endl;
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