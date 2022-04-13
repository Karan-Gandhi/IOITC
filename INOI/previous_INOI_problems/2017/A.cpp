#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long
#define inf 1e10

map<pair<int, int>, bool> arr;
map<pair<int, int>, bool> vis;
ll int ans = 0;
int n, m;

ll int dfs(pair<int, int> u) {
	int i = u.first, j = u.second;
	if (vis[{i, j}]) return 0ll;
	if (!arr[{i, j}]) return 0ll;
	vis[{i, j}] = 1;
	ll int cur = 0;
	if (i != 0 && arr[{i - 1, j}]) {
		cur += dfs({i - 1, j});
	} else {
		cur += 1;
	}
	if (j != 0 && arr[{i, j - 1}]) {
		cur += dfs({i, j - 1});
	} else {
		cur += 1;
	}
	if (i != n - 1 && arr[{i + 1, j}]) {
		cur += dfs({i + 1, j});
	} else {
		cur += 1;
	}
	if (j != m - 1 && arr[{i, j + 1}]) {
		cur += dfs({i, j + 1});
	} else {
		cur += 1;
	}

	return cur;
}

void solve() {
	cin >> n >> m;
	ll int k; cin >> k;
	vector<pair<int, int>> nodes(k);
	for (int i = 0; i < k; i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		nodes[i] = {a, b};
		arr[{a, b}] = 1;
	}

	for (auto node : nodes) {
		if (!vis[node]) {
			ans = max(ans, dfs(node));
		}
	}

	cout << ans << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	solve();
	// ll int t; cin >> t;
	// while (t--) {
	// 	solve();
	// }

	return 0;
}