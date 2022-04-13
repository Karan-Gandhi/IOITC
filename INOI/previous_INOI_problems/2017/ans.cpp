#include <bits/stdc++.h>
using namespace std;

#define pl(a) " [" << #a << ": " << (a) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'
#define ll long long

ll int info(ll int x) {
	string s = to_string(x);
	ll int sum = 0;

	for (char c : s) {
		sum += c - '0';
	}

	return x + sum * sum * sum;
}

void solve() {
	int n; cin >> n;
	ll int init_str; cin >> init_str;
	vector<ll int> str(n + 1);
	str[0] = init_str;
	for (int i = 1; i <= n; i++) {
		str[i] = info(str[i - 1]);
	}
	vector<ll int> e(n + 1); for (int i = 1; i <= n; i++) cin >> e[i];

	// dp[i][j][0-> last day trained 1-> last day battled] = best that we can do till the ith day if we have trained him for j days
	vector<vector<ll int>> dp(n + 1, vector<ll int>(n + 1, 0));
	// base case
	dp[1][0] = init_str * e[1];
	dp[1][1] = 0;

	ll int ans = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= i - 1; j++) {
			if (j - 1 >= 0) {
				dp[i][j] = max({
					dp[i - 1][j - 1],
					dp[i - 1][j] + e[i] * str[j]
				});
			} else {
				dp[i][j] = dp[i - 1][j] + e[i] * str[j];
			}

			ans = max({
				ans,
				dp[i][j]
			});
		}
	}

	// for (auto a : dp) {
	// 	for (auto b : a) {
	// 		cout << b << ' ';
	// 	}
	// 	cout << endl;
	// }

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