#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

ll int inf = 1e9;

void solve() {
	int n, m; cin >> n >> m;

	vector<set<int>> compliment(n);

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		compliment[a].insert(b);
		compliment[b].insert(a);
	}

	int q; cin >> q;

	// vector<pair<pair<int, int>, int>> queries(q);
	vector<pair<vector<pair<int, int>>, int>> queries(n);
	for (int i = 0; i < n; i++) queries[i].second = i;
	
	for (int i = 0; i < q; i++) {
		int a, b; cin >> a >> b;
	
		queries[a].first.emplace_back(b, i);
		queries[b].first.emplace_back(a, i);
	}
	
	vector<bool> done(q);
	vector<int> ans(q);
	vector<int> dist(n, inf);
	
	auto bfs = [&](int start) {
		queue<pair<int, int>> q;
		fill(all(dist), inf);
		set<int> nvis;
		dist[start] = 0;
		// cout << pl(start) << endl;

		q.emplace(start, 0);

		for (int i = 0; i < n; i++) {
			if (i != start) nvis.insert(i);
		}

		while (q.size() != 0 && nvis.size() != 0) {
			auto [node, d] = q.front();
			q.pop();

			vector<int> ne;

			for (int i : nvis) {
				if (compliment[node].count(i) == 0) {
					ne.push_back(i);
				}
			}

			for (int v : ne) {
				if (dist[v] > dist[node] + 1) {
					dist[v] = dist[node] + 1;
					q.emplace(v, dist[v]);
				}

				nvis.erase(v);
			}
		}
	};

	sort(all(queries), [&](auto a, auto b) {
		return a.first.size() > b.first.size();
	});

	for (int i = 0; i < n; i++) {
		vector<pair<int, int>> needed;
		int start = queries[i].second;
		
		for (auto j : queries[i].first) {
			if (!done[j.second]) {
				needed.push_back(j);
			}
		}

		if (needed.size() != 0) {
			bfs(start);

			for (auto j : needed) {
				ans[j.second] = dist[j.first];
				if (ans[j.second] >= inf) ans[j.second] = -1;
				done[j.second] = 1;
			}
		}
	}

	for (int i : ans) cout << i << endl;
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