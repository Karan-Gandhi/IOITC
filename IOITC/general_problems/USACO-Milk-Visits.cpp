#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

string ans;
vector<int> type, start, en;
vector<vector<tuple<int, int, int>>> queries;
vector<bool> done;
int timer = 0, n, m;
vector<vector<int>> adj;
vector<pair<int, int>> last[100005]; // memory??
vector<int> ord;

void dfs(int u, int par, int dep) {
	start[u] = timer++;
	for (int v : adj[u]) if (v != par) dfs(v, u, dep + 1);
	en[u] = timer - 1;
}

bool acc(int a, int b) { // check if b is the ancestor of a
	return start[b] <= start[a] && en[a] <= en[b];
}

void dfs2(int u, int par) {
	// for the current node check the last node 
	last[type[u]].emplace_back(u, ord.size());
	ord.push_back(u);

	for (auto q : queries[u]) {
		if (done[get<2>(q)]) continue; // if the query is already processed
		int t = get<1>(q);

		// check if the child of the last node having the type get<1>(q) is a ancestor of b, if yes then it will not be visited or else no
		if (last[t].size() != 0) {
			int l = last[t].back().first;
			if (l == u) {

				ans[get<2>(q)] = '1';
				ans[get<2>(q)] = '1';
				done[get<2>(q)] = 1;
			} else {
				int son = ord[last[t].back().second + 1];
				if (!acc(get<0>(q), son)) {
					ans[get<2>(q)] = '1';
					done[get<2>(q)] = 1;
				}
			}
		}
	}

	for (int v : adj[u]) {
		if (v == par) continue;
		dfs2(v, u);
	}

	last[type[u]].pop_back();
	ord.pop_back();
}

void solve() {
	cin >> n >> m;

	type.resize(n);
	start.resize(n);
	en.resize(n);
	adj.resize(n);
	queries.resize(n);
	
	done.resize(m);
	ans = string(m, '0');

	// cout << pl(m) << endl;

	fill(all(done), 0);

	for (int i = 0; i < n; i++) {
		cin >> type[i];
	}

	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b;
		a--, b--;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(0, 0, 0);

	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		a--, b--;
		queries[a].push_back(make_tuple(b, c, i));
		queries[b].push_back(make_tuple(a, c, i));
	}

	dfs2(0, 0);

	cout << ans << endl;
}

int main() {
	freopen("milkvisits.in", "r", stdin);
	freopen("milkvisits.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--)
		solve();
}