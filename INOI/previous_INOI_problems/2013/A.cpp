#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pl(var) " [" << #var << ": " << (var) << "] "

ll int inf = 1e16;
ll int mod = 1e9 + 7;
vector<vector<ll int>> dp(1000100, vector<ll int>(2, 0));
vector<ll int> arr(1000100); 

void solve() {
	int n, k; cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> arr[i];

	for (int i = k; i < n; i++) {
		if (i == k) {
			dp[i][0] = dp[i - 1][0] + arr[i];
		} else {
			if (i != 1) {
				dp[i][0] = max(dp[i - 1][0], dp[i - 2][0]) + arr[i];
			} else {
				dp[i][0] = dp[i - 1][0] + arr[i];
			}
		}
	}

	dp[n - 1][1] = dp[n - 1][0];
	for (int i = n - 2; i >= k - 1; i--) {
		if (i != n - 2) {
			dp[i][1] = max(dp[i + 1][1] + arr[i], max(dp[i + 2][1] + arr[i], dp[i][0]));
		} else {
			dp[i][1] = max(dp[i + 1][1] + arr[i], dp[i][0]);
		}
	}

	for (int i = k - 2; i >= 0; i--) {
		if (i != n - 2) {
			dp[i][1] = max(dp[i + 1][1], dp[i + 2][1]) + arr[i];
		} else {
			dp[i][1] = dp[i + 1][1] + arr[i];
		}
	}

	cout << dp[0][1] << endl;
}

int main() {
	solve();

	return 0;
}