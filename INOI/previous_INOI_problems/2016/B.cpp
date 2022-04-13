#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long

void solve() {
	int n; cin >> n;
	int k; cin >> k;
	vector<int> a(n + 1), b(n + 1); 

	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> a[i];

	vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

	function<bool(int, int)> match = [&](int i, int j) -> bool {
		return ((a[j] - a[i]) == k);
	};

	for (int r = 1; r <= n; r++) {
		for (int l = r; l >= 1; l--) {
			// find the max sum in the range [l, r];
			if (l == r) {
				dp[l][r] = 0;
			} else if (l == r - 1 && match(l, r - 1)) {
				dp[l][r] = b[l] + b[r];
			} else {
				// try to find the max for this range
				dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
				if (match(l, r)) {
					dp[l][r] = max(dp[l + 1][r - 1] + b[l] + b[r], dp[l][r]);
				}
				for (int i = l; i < r; i++) {
					dp[l][r] = max(dp[l][r], dp[l][i] + dp[i + 1][r]);
				}
			}
		}
	}
	// cout << pl(dp[1][3]) << endl;
	// for (auto a : dp) {
	// 	for (auto b : a) {
	// 		cout << b << ' ';
	// 	}
	// 	cout << endl;
	// }

	cout << dp[1][n] << endl;
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