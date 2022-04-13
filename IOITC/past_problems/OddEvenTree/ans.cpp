#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

vector<vector<int>> adj;
vector<int> dep;
int allOdd = 0, allEven = 0;

void dfs(int u, int par, int cur_dep) {
	dep[u] = cur_dep;
	
	if (cur_dep % 2 == 0) allEven++;
	else allOdd++;

	for (int v : adj[u]) {
		if (v == par) continue;

		dfs(v, u, cur_dep + 1);
	}
}

void dfs2(int u, int par) {
	
}

void solve() {
	int n; cin >> n;
	adj.resize(n);

	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	// depth is odd
	dfs(0, 0, 0);


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