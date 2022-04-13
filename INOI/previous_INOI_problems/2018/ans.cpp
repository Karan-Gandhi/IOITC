#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long
#define inf 1e16

void solve() {
	ll int n, m, k; cin >> n >> m >> k;
	vector<vector<ll int>> arr(n + 1, vector<ll int>(m + 1, 0));

	for (ll int i = 1; i <= n; i++) {
		ll int cur = 0;
		for (ll int j = 1; j <= m; j++) {
			ll int a; cin >> a;
			cur += a;
			arr[i][j] = cur;
		}
	}

	// find the max and min path
	vector<vector<vector<ll int>>> dp1(n + 1, vector<vector<ll int>>(m + 1, vector<ll int>(k + 1, 0))); // max path
	vector<vector<vector<ll int>>> dp2(n + 1, vector<vector<ll int>>(m + 1, vector<ll int>(k + 1, 0))); // min path

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int l = 0; l <= k; l++) {
				dp1[i][j][l] = dp1[i - 1][j][l];
				dp2[i][j][l] = dp2[i - 1][j][l];

				if (l >= 1) {
					dp1[i][j][l] = max(dp1[i][j][l], dp1[i - 1][j - 1][l - 1]);
					dp2[i][j][l] = min(dp2[i][j][l], dp2[i - 1][j - 1][l - 1]);
				}
				dp1[i][j][k] += arr[i][j];
				dp2[i][j][k] += arr[i][j];
			}
		}
	}

    ll int ans = -1e9;
    for(int a = 0;a<=m;a++){
        for(int b = a+k+2; b<=m; b++)ans = max(ans,dp1[n][b][k] - dp2[n][a][k]);
    }
    cout << ans << endl;

	// for (ll int i = 0; i < m; i++) {
	// 	dp1[n - 1][i][0] = arr[n - 1][i]; // base case
	// 	dp2[n - 1][i][0] = arr[n - 1][i]; // base case
	// }

	// for (ll int i = n - 2; i >= 0; i--) {
	// 	for (ll int j = 0; j < m; j++) {
	// 		dp1[i][j][0] = dp1[i + 1][j][0] + arr[i][j];
	// 		dp2[i][j][0] = dp2[i + 1][j][0] + arr[i][j];

	// 		for (ll int l = 1; l <= k; l++) {
	// 			dp1[i][j][l] = max(dp1[i + 1][j][l], dp1[i + 1][j + 1][l - 1]) + arr[i][j];
	// 			dp2[i][j][l] = min(min(dp2[i + 1][j][l], dp2[i + 1][j + 1][l - 1]) + arr[i][j], dp2[i][j][l - 1]);
	// 		}
	// 	}
	// }

	// for (auto a : dp2) {
	// 	for (auto b : a) {
	// 		cout << b[2] << ' ';
	// 	}
	// 	cout << endl;
	// }

	// ll int ans = -inf;

	// for (ll int i = 0; i < m; i++) {
	// 	for (ll int j = 0; j < i; j++) {
	// 		for (ll int l = 0; l <= k; l++) { // ends at i + l
	// 			// ends at j + l'
	// 			// i + l - j - l' = k + 1
	// 			if (i + l - j - k - 1 < 0) continue;
	// 			ans = max(ans, dp1[0][i][l] - dp2[0][j][i + l - j - k - 1]);
	// 		}
	// 	}
	// }

	// cout << ans << endl;

	// dp1 - dp2
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