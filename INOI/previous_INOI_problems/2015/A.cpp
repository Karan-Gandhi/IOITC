#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long

void solve() {
	int n; cin >> n;
	vector<ll int> a(n), b(n); 
	for (int i = 0; i < n; i++) cin >> a[i]; 
	for (int j = 0; j < n; j++) cin >> b[j];

	if (n == 1) {
		cout << a[0] << endl;
		return;
	}

	if (n == 2) {
		cout << max({a[0], a[1], a[0] + a[1]}) << endl;
		return;
	}

	vector<ll int> pref(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		pref[i] = pref[i - 1] + b[i - 1];
	}

	function<ll int(int, int)> sum = [&](int a, int b) -> ll int {
		if (b > n || a >= n || a > b) return 0ll;
		return pref[b + 1] - pref[a];
	};

	vector<ll int> dp(n + 1, -1e16);
	// dp[0] = -1e16;
	for (int i = 1; i < n; i++) {
		dp[i] = max(dp[i - 1] - a[i - 1] + b[i - 1] + a[i], a[i - 1] + a[i]);
	}

	vector<ll int> dp1(n + 1, -1e16);
	// dp1[0] = -1e16;
	dp1[1] = (a[0] + a[1] + sum(2, n - 1));

	for (int i = 2; i < n; i++) {
		dp1[i] = max(sum(0, i - 2) + sum(i + 1, n - 1) + a[i - 1] + a[i], dp1[i - 1] - a[i - 1] - b[i] + a[i]);
	}

	ll int ans = 0;
	for (int i = 0; i < n; i++) {
		// cout << pl(i) << pl(dp[i]) << pl(dp1[i]) << pl(a[i]) << endl;
		ans = max({ans, dp1[i], dp[i], a[i]});
	}

	cout << ans << endl;
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