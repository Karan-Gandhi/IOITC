#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(ll int i = 0; i < (ll int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}

ll int inf = 1e18;

vector<ll int> distancesS, distancesU, distancesV, distances;
vector<vector<pair<int, ll int>>> adj;
vector<vector<int>> from;
vector<bool> vis;

void djkstra(ll int start) {
	fill(all(distances), inf);

	distances[start] = 0;
	priority_queue<pair<ll int, ll int>> pq;
	pq.emplace(0, start);

	while (pq.size()) {
		ll int node, d;
		tie(d, node) = pq.top();
		pq.pop();
		d = -1 * d;

		if (distances[node] != d) continue;

		for (auto [v, wt] : adj[node]) {
			ll int new_dist = d + wt;

			if (new_dist < distances[v]) {
				distances[v] = new_dist;
				pq.emplace(-new_dist, v);
			}
		}
	}
}

ll int ans = 0;
vector<ll int> mem;

ll int dfs2(ll int u) {
	if (vis[u]) return mem[u];
	vis[u] = 1;

	ll int mn = inf;
	for (ll int v : from[u]) {
		mn = min(mn, dfs2(v));
	}

	ans = min(ans, mn + distancesV[u]);
	return mem[u] = min(mn, distancesU[u]);
}

void solve() {
	int n, m; cin >> n >> m;
	int s, t; cin >> s >> t; s--, t--;
	int U, V; cin >> U >> V; U--, V--;

	adj.resize(n);
	vis.resize(n);
	distances.resize(n);
	distancesS.resize(n);
	distancesU.resize(n);
	distancesV.resize(n);
	from.resize(n);
	mem.resize(n);
	

	for (ll int i = 0; i < m; i++) {
		ll int a, b, c; cin >> a >> b >> c;
		a--, b--;
		adj[a].emplace_back(b, c);
		adj[b].emplace_back(a, c);
	}

	// run djkstra
	djkstra(U); for (ll int i = 0; i < n; i++) distancesU[i] = distances[i];
	djkstra(V); for (ll int i = 0; i < n; i++) distancesV[i] = distances[i];

	auto djkstra1 = [&]() {
		// I know u and v
		fill(all(distancesS), inf);

		distancesS[s] = 0;

		priority_queue<pair<ll int, ll int>> pq;
		pq.emplace(0, s);

		while (pq.size()) {
			auto [dist, node] = pq.top();
			pq.pop();
			dist = dist * -1;

			if (distancesS[node] != dist) continue;

			for (auto [v, wt] : adj[node]) {
				ll int new_dist = dist + wt;

				if (new_dist < distancesS[v]) {
					distancesS[v] = new_dist;
					from[v].clear();
					from[v].push_back(node);
					pq.emplace(-new_dist, v);
				} else if (new_dist == distancesS[v]) {
					from[v].push_back(node);
				}
			}
		}
	};

	djkstra1();

	ans = distancesU[V];

	fill(all(mem), 0);
	dfs2(t);

	distancesV.swap(distancesU);
	fill(all(vis), 0);
	fill(all(mem), inf);
	dfs2(t);

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll int T = 1;
	// cin >> T;
	while (T--) 
		solve();

	return 0;
}