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
			if (l == r) dp[l][r] = 0;
			else {
				dp[l][r] = dp[l][r - 1]; // base case

				for (int i = l; i < r; i++) {
					if (match(i, r)) {
						dp[l][r] = max(dp[l][r], dp[l][i - 1] + dp[i + 1][r - 1] + b[i] + b[r]);
					}
				}
			}
		}
	}

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