#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long

ll int inf = 1e16;
vector<vector<ll int>> dp(5004, vector<ll int>(5004, 0));

void solve() {
	int n, m; cin >> n >> m;
	int c[n + 1]; for (int i = 0; i < n; i++) cin >> c[i + 1];
	vector<pair<int, int>> p(m + 1); 
	for (int i = 0; i < m; i++) cin >> p[i + 1].second;
	for (int i = 0; i < m; i++) cin >> p[i + 1].first;

	sort(all(p));

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			dp[i][j] = inf;
			if (i == 0 && j == 0) dp[i][j] = 0;
			// try to finish a public job here
			if (j - 1 >= 0) { // dp[i][j] = min time taken to complete the last job, machine not available at this time
				if (dp[i][j - 1] >= p[j].first) { // can't start a even here
					dp[i][j] = inf;
				} else if (dp[i][j - 1] + p[j].second > p[j].first) {
					dp[i][j] = dp[i][j - 1] + p[j].second;
				} else {
					dp[i][j] = p[j].first;
				}
			}

			// try to finish a classified job here
			if (i - 1 >= 0) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j] + c[i]);
			}
		}
	}

	if (dp[n][m] >= inf) {
		cout << -1 << endl;
		return;
	}

	cout << dp[n][m] << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	// solve();
	int t; cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}