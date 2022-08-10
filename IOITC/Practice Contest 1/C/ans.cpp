#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

int inf = 1e9;

void solve() {
	int n, m; cin >> n >> m;
	vector<set<int>> compliment(n);

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;

		compliment[a].insert(b);
		compliment[b].insert(a);
	}

	vector<vector<int>> adj(n);

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (compliment[i].count(j) == 0) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}

	// auto bfs = [&](int )
	vector<vector<int>> dist(n, vector<int>(n, inf));
	vector<vector<bool>> vis(n, vector<bool>(n, 0));

	for (int start = 0; start < n; start++) {
		queue<int> q;
		dist[start][start] = 0;
		q.push(start);
		vis[start][start] = 1;

		for (int i = 0; i < start; i++) {
			if (dist[i][start] >= inf) continue;
			dist[start][i] = dist[i][start];
			q.push(i);
			vis[start][i] = 1;
		}

		while (q.size() != 0) {
			int node = q.front();
			q.pop();

			for (int v : adj[node]) {
				if (!vis[start][v]) {
					vis[start][v] = 1;
					dist[start][v] = dist[start][node] + 1;
					q.push(v);
				}
			}
		}
	}

	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b; cin >> a >> b;
		cout << (dist[a][b] >= inf ? -1 : dist[a][b]) << endl;
	}
}

int main() {
#ifdef LOCAL
    auto clock_start = chrono::high_resolution_clock::now();
    cout << endl;
#endif

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) 
		solve();

#ifdef LOCAL
    auto clock_end = chrono::high_resolution_clock::now();
    cout << endl;
    chrono::duration<double> elapsed = clock_end - clock_start;
    cout << "Execution time: " << elapsed.count() << "s" << endl;
#endif

	return 0;
}