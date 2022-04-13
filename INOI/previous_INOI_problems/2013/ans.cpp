#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pl(var) " [" << #var << ": " << (var) << "] "

void solve() {
	int n, k; cin >> n >> k;
	vector<ll int> arr(n + 1, 0); for (int i = 1; i <= n; i++) cin >> arr[i];

	vector<vector<ll int>> dp(n + 3, vector<ll int>(2, -1e16));
	dp[k][0] = 0;
	for (int i = k + 1; i <= n; i++) {
		dp[i][0] = max(dp[i - 1][0], dp[i - 2][0]) + arr[i];
	}

	dp[n][1] = dp[n][0];
	for (int i = n - 1; i >= k; i--) {
		dp[i][1] = max({
			dp[i][0],
			dp[i + 1][1] + arr[i],
			dp[i + 2][1] + arr[i]
		});
	}

	for (int i = k - 1; i >= 1; i--) {
		dp[i][1] = max({
			dp[i + 1][1],
			dp[i + 2][1]
		}) + arr[i];
	}

	cout << dp[1][1] << endl;
}

int main() {
	solve();

	return 0;
}