#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

vector<vector<int>> adj;
vector<int> dep;
int ans = 0;

void dfs(int u, int d = 0) {
	ans += d;
	dep[u] = d;

	for (int v : adj[u]) {
		dfs(v, d + 1);
	}
}

void solve() {
	adj.clear();
	dep.clear();
	ans = 0;

	int n; cin >> n;

	if (n == 1) {
		cout << 0 << endl;
		return;
	}

	vector<int> p(n);
	adj.resize(n);
	dep.resize(n);

	p[0] = 0;
	vector<int> leafs;
	vector<int> degree(n, 0);
	for (int i = 1; i < n; i++) {
		cin >> p[i];
		p[i]--;
		adj[p[i]].push_back(i);
		degree[p[i]]++;
		degree[i]++;
	}

	for (int i = 0; i < n; i++) {
		if (degree[i] == 1) leafs.push_back(i);
	}

	dfs(0);

	multiset<pair<int, int>> leaves;
	for (int i : leafs) {
		leaves.insert(make_pair(dep[i], i));
	}
	int cur = ans;
	while (leaves.size() != 0) {
		int best = leaves.begin()->first;
		int id = leaves.begin()->second;
		if (id == 0) break;
		leaves.erase(leaves.begin());

		cur -= best;
		ans += cur;

		// cout << pl(id) << pl(ans) << pl(cur) << endl;
		int next = p[id];
		degree[next]--;

		if (next != 0 && degree[next] == 1) {
			leaves.insert(make_pair(best - 1, next));
		}
	}

	cout << ans << endl;
}

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	cin >> T;
	while (T--)
		solve();
}