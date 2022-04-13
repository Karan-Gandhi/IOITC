#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}

vector<vector<pair<int, ll int>>> adj;

ll int inf = 1e16;

void solve() {
	int n; cin >> n;
	int e; cin >> e;
	int k; cin >> k;

	vector<int> vc;
	for (int i = 0; i < k; i++) {
		int a; cin >> a;
		vc.push_back(a);
	}

	adj.resize(n);

	for (int i = 0; i < e; i++) {
		int a, b; ll int c; cin >> a >> b >> c;
		adj[b].emplace_back(a, c);
	}

	int q; cin >> q;
	vector<ll int> qq(q); 
	for (int i = 0; i < n; i++) {
		cin >> qq[i];
		int pp; for (int i = 0; i < 5; i++) cin >> pp;
	}

	vector<ll int> ans(q, inf);

	for (int i = 0; i < k; i++) {
		vector<ll int> dist(n, inf);
		priority_queue<pair<ll int, int>> pq;
		dist[vc[i]] = 0;
		pq.push({0, vc[i]});
		vector<bool> vis(n, 0);

		while (!pq.empty()) {
			int a = pq.top().second;
			pq.pop();

			if (vis[a]) continue;
			vis[a] = 1;

			for (auto v : adj[a]) {
				int b = v.first; ll int w = v.second;
				// cout << pl(b) << endl;
				if (dist[a] + w < dist[b]) {
					dist[b] = dist[a] + w;
					pq.push(make_pair(-dist[b], b));
				}
			}
		}

		for (int i = 0; i < q; i++) {
			ans[i] = min(ans[i], dist[qq[i]]);
		}
	}

	for (ll int a : ans) {
		if (a >= inf) a = -1;
		cout << a << endl;
	}

	// while (q--) {
	// 	int s; cin >> s;
	// 	int pp; for (int i = 0; i < 5; i++) cin >> pp;
	// 	if (dist[s] >= inf) dist[s] = -1;
	// 	cout << dist[s] << endl;
	// }


	// vector<vector<ll int>> dist(k, vector<ll int>(n, inf)); // dist[n][k] = distance bw the nth and the kth voting city

	// for (int i = 0; i < k; i++) {
	// 	dist[i][vc[i]] = 0;
	// 	priority_queue<pair<ll int, int>> pq;
	//	pq.push({0, vc[i]});
	// 	vector<bool> vis(n, 0);

	// 	while (!pq.empty()) {
	// 		int a = pq.top().second;
	// 		pq.pop();

	// 		if (vis[a]) continue;
	// 		vis[a] = 1;

	// 		for (auto v : adj[a]) {
	// 			int b = v.first; ll int w = v.second;
	// 			// cout << pl(b) << endl;
	// 			if (dist[i][a] + w < dist[i][b]) {
	// 				dist[i][b] = dist[i][a] + w;
	// 				pq.push(make_pair(-dist[i][b], b));
	// 			}
	// 		}
	// 	}
	// }

	// int q; cin >> q;
	// while (q--) {
	// 	int s; cin >> s;
	// 	int p; for (int i = 0; i < 5; i++) cin >> p;
	// 	ll int ans = inf;
	// 	for (int i = 0; i < k; i++) {
	// 		ans = min(ans, dist[s][i]);
	// 	}

	// 	if (ans >= inf) {
	// 		ans = -1;
	// 	}

	// 	cout << ans << endl;
	// }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) 
		solve();

	return 0;
}