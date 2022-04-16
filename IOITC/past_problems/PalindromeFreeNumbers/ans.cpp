#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

ll int dp[11][11][20][2];

ll int f(ll int prev, ll int pprev, ll int n, bool all, string& cur) {
	if (n >= (ll int)cur.size()) return 1;
	if (dp[prev][pprev][n][all] != -1) return dp[prev][pprev][n][all];

	if (all) {
		ll int res = 0;
		for (ll int i = 0; i <= 9; i++) {
			if (i == prev || i == pprev) continue;
			res += f(i, prev, n + 1, 1, cur);
		}

		return dp[prev][pprev][n][all] = res;
	} else {
		ll int last = cur[n] - '0';
		ll int res = 0;
		for (ll int i = 0; i <= last; i++) {
			if (i == prev || i == pprev) continue;
			if (i == last) {
				res += f(i, prev, n + 1, 0, cur);
			} else {
				res += f(i, prev, n + 1, 1, cur);
			}
		}

		return dp[prev][pprev][n][all] = res;
	}
}

ll int g(ll int n) {
	if (n < 0) return 0;

	string s = to_string(n);
	ll int first = s[0] - '0';
	ll int res = 1; // always count 0
	
	memset(dp, -1, sizeof dp);
	
	for (ll int i = 1; i <= first; i++) {
		res += f(i, i, 1, i != first, s);
	}

	for (ll int k = 2; k <= (int)s.size(); k++) {
		for (ll int i = 1; i < 10; i++) {
			res += f(i, i, k, 1, s);
		}
	}

	return res;
}

void solve() {
	ll int a, b; cin >> a >> b;
	cout << g(b) - g(a - 1) << endl;
}

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll int T = 1;
	// cin >> T;
	while (T--)
		solve();
}