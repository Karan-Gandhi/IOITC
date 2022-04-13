#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long

void solve() {
	ll int n, mod; cin >> n >> mod;

	vector<ll int> dp(n + 1);
	dp[0] = 0;
	dp[1] = 2;
	ll int pow = 4;
	for (int i = 2; i <= n; i++) {
		dp[i] = pow;
		// cout << pl(i) << endl;
		for (int j = 1; j * j <= i; j++) {
			if (i % j == 0) {
				// try j and i / j
				if (i/j != j && j != 1) dp[i] -= (dp[j] + dp[i / j]);
				else dp[i] -= dp[j];
				// cout << pl(dp[j]) << pl(dp[i / j]) << pl(j) << endl;
			}
		}
		// dp[i] = (pow - dp[i]);
		while (dp[i] < 0) dp[i] += mod;
		pow *= 2;
		pow %= mod;
		dp[i] %= mod;
		// cout << pl(dp[i]) << endl;
	}

	// cout << dp[2] << endl;
	cout << dp[n] << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	solve();
	// int t; cin >> t;
	// while (t--) {
	// 	solve();
	// }

	return 0;
}