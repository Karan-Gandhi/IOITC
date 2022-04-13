#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long

void solve() {
	int n, l; cin >> n >> l;
	vector<pair<int, int>> arr(n); for (int i = 0; i < n; i++) {
		int a; cin >> a;
		arr[i] = make_pair(a, i);
	}

	if (l > n) {
		cout << 0 << endl;
		return;
	}
	if (n == 1) {
		cout << 0 << endl;
		return;
	}

	function<int(int, int)> cost = [&](int i, int j) -> int {
		return abs(arr[i].second - arr[j].second);
	};

	sort(all(arr)); // pick L numbers such that min(a[i + 1] - a[i]) is max
	reverse(all(arr)); // what if I compute all the n(n - 1) costs and the choose the max one

	// dp[i][j] = max of the min cost of intresting subsequence of size j till the ith index and the ith element is surely a part of it
	// dp[i][j] = max of min(dp[i - k][j - 1], cost(i-k th element, ith element))
	// ans = max of (dp[i][l]);
	for (auto a : arr) {
		cout << pl(a.first) << pl(a.second) << endl;
	}

	vector<vector<int>> dp(n + 1, vector<int>(l + 1, 0));
	dp[1][2] = cost(0, 1);

	for (int i = 2; i < n; i++) {
		for (int j = 0; j < i; j++) {
			dp[i][2] = max(dp[i][2], cost(i, j));
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 3; j <= l; j++) {
			dp[i][j] = 0;
			for (int k = 0; k < i; k++) {
				dp[i][j] = max(dp[i][j], min(dp[k][j - 1], cost(k, i)));
			}
		}
	}

	for (auto a : dp) {
		for (auto b : a) {
			cout << b << ' ';
		}
		cout << endl;
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans = max(ans, dp[i][l]);
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