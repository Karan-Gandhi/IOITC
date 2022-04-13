#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long
#define inf 1e16

void solve() {
	ll int n, m, k; cin >> n >> m >> k;
	// assert(k == 0);
	vector<vector<ll int>> arr(n, vector<ll int>(m, 0));
	for (ll int i = 0; i < n; i++) 
		for (ll int j = 0; j < m; j++) 
			cin >> arr[i][j];


	// compute the prefix of each row
	vector<vector<ll int>> pref(n, vector<ll int>(m + 1, 0));
	
	for (ll int i = 0; i < n; i++) {
		ll int cur = 0;
		for (ll int j = 0; j < m; j++) {
			cur += arr[i][j];
			pref[i][j] = cur;
		}
	}

	vector<vector<ll int>> dp(n, vector<ll int>(m, -1e10));

	// start at the bottom most cell
	dp[n - 1][m - 1] = pref[n - 1][m - 1];

	for (ll int i = n - 2; i >= 0; i--) {
		for (ll int j = m - 1; j >= 0; j--) {
			if (j == m - 1) {
				dp[i][j] = dp[i + 1][j] + pref[i][j];
			} else {
				dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + pref[i][j];
			}
		}
	}

	ll int ans = int(-1e10);
	for (ll int i = 1; i < m; i++) {
		ans = max(ans, dp[0][i]);
	}
	cout << ans << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	// solve();
	ll int t; cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}