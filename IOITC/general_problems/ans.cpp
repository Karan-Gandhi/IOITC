#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

void solve() {
	int n = 7;

	vector<int> arr(n);
	iota(all(arr), 1);

	int ans = 0;
	do {
		bool ok = 0;
		bool good = 0;

		for (int i = 0; i < n - 1; i++) {
			if (arr[i] > arr[i + 1] && !ok) {
				ok = 1;
				good = 1;
			} else if (arr[i] > arr[i + 1]) {
				good = 0;
			}
		}

		if (good) {
			// for (int i : arr) cout << i << ' ';

			// cout << endl;
		}

		ans += good;
	} while (next_permutation(all(arr)));

	vector<int> dp(n + 1);
	dp[2] = 1;

	for (int i = 3; i <= n; i++) {
		dp[i] = 2 * dp[i - 1] + i - 1;
	}

	cout << dp[n] << endl;

	cout << ans << endl;
}

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--)
		solve();
}