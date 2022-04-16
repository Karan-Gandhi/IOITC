#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

vector<vector<ll int>> adj;
vector<pair<ll int, ll int>> ans;
vector<ll int> dep, oddChild, evenChild;
ll int totOdd, totEven;

void dfs(ll int u, ll int par, ll int cur) {
	dep[u] = cur;

	if (cur % 2 == 0) {
		totEven++;
		evenChild[u]++;
	} else {
		totOdd++;
		oddChild[u]++;
	}

	for (ll int v : adj[u]) {
		if (v == par) continue;
		dfs(v, u, cur + 1);

		oddChild[u] += oddChild[v];
		evenChild[u] += evenChild[v];
	}
}

void dfs2(ll int u, ll int par) {
	// number of odd vertices passing through u = number of odd in subtree * even except subtree
	ans[u].first = oddChild[u] * (totEven - evenChild[u]) + evenChild[u] * (totOdd - oddChild[u]);
	ans[u].second = evenChild[u] * (totEven - evenChild[u]) + oddChild[u] * (totOdd - oddChild[u]);
	ll int curE = 0;
	ll int curO = 0;
	for (ll int v : adj[u]) {
		if (v == par) continue;
		curO += oddChild[v] * (evenChild[u] - (dep[u] % 2 == 0) - evenChild[v]) + evenChild[v] * (oddChild[u] - (dep[u] % 2 == 1) - oddChild[v]);
		curE += evenChild[v] * (evenChild[u] - (dep[u] % 2 == 0) - evenChild[v]) + oddChild[v] * (oddChild[u] - (dep[u] % 2 == 1) - oddChild[v]);
	}
	curO /= 2;
	curE /= 2;
	// cout << pl(curO) << pl(curE) << endl;
	if (dep[u] % 2 == 0) {
		ans[u].first += curO + oddChild[u];
		ans[u].second += curE + evenChild[u];
	} else {
		ans[u].first += curO + evenChild[u];
		ans[u].second += curE + oddChild[u];
	}
	// ans[u].second++; // always consider a empty route

	for (ll int v : adj[u]) {
		if (v == par) continue;
		dfs2(v, u);
	}
}

void solve() {
	ll int n; cin >> n;

	totOdd = totEven = 0;
	adj.resize(n);
	ans.resize(n);
	dep = oddChild = evenChild = vector<ll int>(n, 0);

	for (ll int i = 0; i < n - 1; i++) {
		ll int a, b; cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(0, 0, 0);
	totOdd = oddChild[0];
	totEven = evenChild[0];
	dfs2(0, 0);

	for (auto a : ans) {
		cout << a.first << ' ' << a.second << endl;
	}
}

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll int T = 1;
	// cin >> T;
	while (T--)
		solve();
}