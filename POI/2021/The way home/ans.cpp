#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(ll int i = 0; i < (ll int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

ll int inf = 1e16;

void solve() {
	ll int n, m, s, K, t; cin >> n >> m >> s >> K >> t;

	vector<vector<pair<int, ll int>>> adj(n);
	vector<pair<ll int, ll int>> info(s);
	vector<vector<ll int>> costs(s);
	vector<vector<int>> busStops(n);
	vector<vector<int>> seq(s);
	map<int, int> idx[s];

	for (int i = 0; i < m; i++) {
		int a, b; ll int c; cin >> a >> b >> c;

		a--, b--;

		adj[a].emplace_back(b, c);
		adj[b].emplace_back(a, c);
	}
	
	for (int i = 0; i < s; i++) {
		int l; cin >> l >> info[i].first >> info[i].second;

		ll int cur_cost = 0;
		int prev = -1;

		for (int j = 0; j < l; j++) {
			
			int a; cin >> a;
			a--;
			
			seq[i].push_back(a);
			idx[i][a] = j;
			busStops[a].push_back(i);
			
			if (prev == -1) {
				costs[i].push_back(cur_cost);
			}
			
			if (prev != -1) {
				for (auto [v, wt] : adj[prev]) {
					if (v == a) {
						cur_cost += wt;
						costs[i].push_back(cur_cost);
						break;
					}
				}
			}

			prev = a;
		}
	}

	auto get_earliest = [&](ll int t, int bus, int stop) {
		ll int c = costs[bus][stop];
		ll int new_bus_start_time = info[bus].first + c;

		ll int j = (t - new_bus_start_time + info[bus].second - 1) / info[bus].second;
		if (j < 0) j = 0;
		return new_bus_start_time + j * info[bus].second;
	};

	vector<vector<ll int>> dp(K + 2, vector<ll int>(n, inf));
	dp[0][0] = t;

	vector<vector<ll int>> ndp(s);

	for (int i = 0; i < s; i++) {
		for (int cnt = 0; cnt < (int)seq[i].size(); cnt++) {
			int k = 0;
			if (cnt) ndp[i].push_back(min(ndp[i][cnt - 1], get_earliest(dp[k][seq[i][cnt]], i, cnt) - costs[i][cnt]));
			else ndp[i].push_back(get_earliest(dp[k][seq[i][cnt]], i, cnt) - costs[i][cnt]);
		}
	}


	for (int k = 1; k <= K + 1; k++) {
		for (int u = 0; u < n; u++) {
			dp[k][u] = dp[k - 1][u];
			
			for (int i : busStops[u]) {
				int cntU = idx[i][u];
				dp[k][u] = min(dp[k][u], ndp[i][cntU] + costs[i][cntU]);
			}
		}

		for (auto &i : ndp) {
			fill(all(i), inf);
		} 

		for (int i = 0; i < s; i++) {
			for (int cnt = 0; cnt < (int)seq[i].size(); cnt++) {
				if (cnt != 0) ndp[i][cnt] = (min(ndp[i][cnt - 1], get_earliest(dp[k][seq[i][cnt]], i, cnt) - costs[i][cnt]));
				else ndp[i][cnt] = (get_earliest(dp[k][seq[i][cnt]], i, cnt) - costs[i][cnt]);
			}
		}
	}

	if (dp[K + 1][n - 1] >= inf) {
		cout << "NIE" << endl;
	} else {
		cout << dp[K + 1][n - 1] << endl;
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