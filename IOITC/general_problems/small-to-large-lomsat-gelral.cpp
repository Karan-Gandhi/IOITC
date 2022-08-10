#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

vector<vector<int>> adj;
map<int, int> occ[100005];
ll int sum[100005];
int freq[100005];
ll int ans[100005];
vector<int> col;

void merge(int a, int b) {
	if (occ[a].size() > occ[b].size()) { // always add to b
		occ[a].swap(occ[b]);
		swap(freq[a], freq[b]);
		swap(sum[a], sum[b]);
	}

	for (auto [color, cnt] : occ[a]) {
		occ[b][color] += cnt;

		if (occ[b][color] > freq[b]) {
			sum[b] = color;
			freq[b] = occ[b][color];
		} else if (occ[b][color] == freq[b]) {
			sum[b] += color;
		}
	}
}

void dfs(int u, int par) {
	freq[u] = 1;
	sum[u] = col[u];
	occ[u][col[u]]++;

	for (int v : adj[u]) {
		if (v == par) continue;

		dfs(v, u);
		merge(v, u);
	}
	ans[u] = sum[u];
}

void solve() {
	int n; cin >> n;
	col.resize(n);

	for (int i = 0; i < n; i++) cin >> col[i];
	adj.resize(n);

	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b;
		a--, b--;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(0, 0);

	for (int i = 0; i < n; i++) cout << ans[i] << ' ';
	cout << endl;
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