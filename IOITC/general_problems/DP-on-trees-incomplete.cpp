#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

vector<vector<int>> ans;
vector<vector<pair<int, int>>> adj;
vector<bool> deleted;
vector<pair<int, int>> rm, add;


void dfs(int u, int par, int came_from) {
	for (auto v : adj[u]) {
		if (v.first == par) continue;

		dfs(v.first, u, v.second);
	}

	int degree = adj[u].size();
	degree -= 1;

	if (degree == 2) {
		// delete the edge b/w the par and the child
		if (came_from != -1) {
			deleted[came_from] = 1;
			rm.emplace_back(u, par);
		}
	} else if (degree < 2) {
		// do nothing
		return;
	} else {
		// delete the edge b/w
		for (auto [_, idx] : adj[u]) {
			if (_ == par) continue;
			degree -= deleted[idx];
		}

		if (degree < 2) {
			return;
		} else {
			if (came_from != -1) {
				// delete the parent
				deleted[came_from] = 1;
				
			}
		}
	}
}

void solve() {
	int n; cin >> n;
	adj.resize(n);
	deleted.resize(n - 1);

	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b;

		adj[a].emplace_back(b, i);
		adj[b].emplace_back(a, i);
	}

	dfs(0, 0, -1);
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