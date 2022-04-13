#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

ll int inf = 1e16;

void solve() {
	int n, m; cin >> n >> m;

	vector<vector<pair<int, ll int>>> adj(n + 1);

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		ll int c; cin >> c;
		adj[a - 1].emplace_back(b - 1, c);
	}

	vector<vector<ll int>> dist(n + 1, {inf, inf});

	priority_queue<tuple<ll int, bool, int>> pq;
	dist[0] = {0, 0};
	pq.push(make_tuple(0, 0, 0));

	while (pq.size() != 0) {
		int u = get<2>(pq.top());
		ll int cur_dist = -1 * get<0>(pq.top());
		bool disc_used = get<1>(pq.top());
		pq.pop();

		if (dist[u][disc_used] != cur_dist) continue;

		for (auto [v, cost] : adj[u]) {
			ll int new_dist = cur_dist + cost;

			if (new_dist < dist[v][disc_used]) {
				dist[v][disc_used] = new_dist;
				pq.push(make_tuple(-new_dist, disc_used, v));
			}

			if (!disc_used) {
				new_dist = cur_dist + cost / 2;

				if (new_dist < dist[v][1]) {
					dist[v][1] = new_dist;
					pq.push(make_tuple(-new_dist, 1, v));
				}
			}
		}
	}

	cout << dist[n - 1][1] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--)
		solve();
}