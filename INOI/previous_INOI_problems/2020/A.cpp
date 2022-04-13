#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

int n, m;
vector<int> dep_id; // dep_id[i] = id of the department it belongs to
vector<vector<int>> dep;
vector<vector<int>> adj;
vector<bool> vis;

ll int get_depth(int u, int depth) {
	if (vis[u]) return 0;
	// cout << pl(u) << pl(depth) << endl;
	vis[u] = 1;
	ll int res = depth;

	for (int v : adj[u]) {
		if (!vis[v]) {
			res += get_depth(v, depth + 1);
		}
	}

	return res;
}

void solve() {
	dep_id.clear();
	dep.clear();
	adj.clear();
	vis.clear();

	cin >> n >> m;
	dep_id.resize(n + 1);
	adj.resize(n + 1);
	vis.resize(n + 1);
	fill(all(dep_id), -1);
	fill(all(vis), 0);

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		if (dep_id[a] == -1 && dep_id[b] == -1) {
			// create a new department with a and b in it
			dep_id[a] = dep_id[b] = dep.size();
			dep.push_back({a, b});
		} else {
			if (dep_id[a] == -1) swap(a, b);

			assert(dep_id[b] == -1);
			assert(dep_id[a] != -1);

			dep[dep_id[a]].push_back(b);
			dep_id[b] = dep_id[a];
		}

		adj[a].push_back(b); // add a edge
		adj[b].push_back(a);
	}

	for (int i = 0; i < n; i++) {
		if (dep_id[i + 1] == -1) {
			// odd type dep
			dep_id[i + 1] = dep.size();
			dep.push_back({i + 1});
		}
	}

	ll int even = 0;
	ll int odd = 0;

	for (auto cur_dep : dep) {
		if (int(cur_dep.size()) % 2 == 0) {
			// type even
			int head = cur_dep[0];
			for (auto a : cur_dep) head = min(a, head);
			even += get_depth(head, 1);
		} else {
			// type odd
			int head = cur_dep[0];
			for (auto a : cur_dep) head = max(a, head);
			odd += get_depth(head, 1);
		}
	}

	cout << even << ' ' << odd << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int t; cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}