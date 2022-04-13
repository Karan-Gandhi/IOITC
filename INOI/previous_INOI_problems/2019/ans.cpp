#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long

int n, l;
vector<pair<ll int, ll int>> arr(3003);

bool possible(ll int cost) {
	vector<ll int> dp(n + 1, 1);

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (abs(arr[i].second - arr[j].second) >= cost) {
				dp[i] = max(dp[i], dp[j] + 1ll);
			}
		}
		if (dp[i] >= l) return 1;
	}

	return 0;
}

void solve() {
	cin >> n >> l;
	for (int i = 0; i < n; i++) cin >> arr[i].first;
	for (int i = 0; i < n; i++) arr[i].second = (i + 1);
	sort(all(arr));
	reverse(all(arr));

	ll int hi = n - 1, lo = 0;
	ll int ans = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i].first == arr[j].first) {
				ans = max(ans, abs(arr[i].second - arr[j].second));
			}
		}
	}

	while (hi >= lo) {
		ll int mid = (hi + lo) / 2;
		if (possible(mid)) {
			ans = max(ans, mid);
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}

	cout << ans << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	// solve();
	int t; cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}