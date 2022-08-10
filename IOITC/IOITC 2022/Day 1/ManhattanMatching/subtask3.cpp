#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pl(var) " [" << #var << ": " << (var) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'

void solve() {
	int n, k; cin >> n >> k;
	// assert(k == 1);

	// vector<int> arr(n);

	// for (int i = 0; i < n; i++) {
	// 	cin >> arr[i];
	// }

	// sort(all(arr));

	// // split into n/2 sections
	// ll int ans = 0;
	// for (int i = 0; i < n / 2; i++) {
	// 	ans += arr[n / 2 + i] - arr[i];
	// }

	// cout << ans << endl;
	// for (int i = 0; i < n / 2; i++) {
	// 	cout << (n / 2 + i + 1) << ' ' << (i + 1) << endl;
	// }
	// cout << pl(n) << pl(k) << endl;
	assert(k == 3);

	vector<tuple<int, int, int>> arr(n);

	for (int i = 0; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		arr[i] = make_tuple(a, b, c);
	}
	vector<int> dp(1 << n);

	auto info = [&](int a, int b) {
		auto [x1, y1, z1] = arr[a];
		auto [x2, y2, z2] = arr[b];

		return abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2);
	};

	for (int mask = 2; mask < (1 << n); mask++) {
		if (__builtin_popcount(mask) % 2 != 0) {
			continue;
		}

		for (int bit1 = 0; bit1 < n; bit1++) {
			if (mask & (1 << bit1)) {
				for (int bit2 = bit1 + 1; bit2 < n; bit2++) {
					if (mask & (1 << bit2)) {
						dp[mask] = max(dp[mask ^ (1 << bit1) ^ (1 << bit2)] + info(bit1, bit2), dp[mask]);
					}
				}
			}
		}
	}

	cout << dp[(1 << n) - 1] << endl;
}

int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(nullptr);

	int T = 1;
	cin >> T;

	while (T--) {
		solve();
	}
}