#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

void solve() {
	int n, k; cin >> k >> n;

	if (k == 1) {
		if (n % 3 == 0) {
			cout << 1 << endl;
		} else {
			cout << 0 << endl;
		}
	} else if (k == 2) {
		vector<ll int> dp(n + 1, 0);
		dp[0] = 1;
		dp[2] = 1;
		for (int i = 3; i <= n; i++) {
			dp[i] = dp[i - 2] + dp[i - 3];
			dp[i] = (dp[i] % int(1e9 + 7));
		}

		cout << dp[n] << endl;
	} else if (k == 3) {
		// x x . . .
		// x x . . .
		// x x x . .

		// x x . . . . .
		// x x . . . . .
		// x x x x . . .

		// . . .
		// . . .
		// . . .

		// f(x) = # of ways to fill when all the 3 cells are empty
		// g(x) = # of ways to fill when bottom 3 cells is filled excluding 3 lines
		// h(x) = # of ways to fill when only bottom left cell is filled
		// i(x) = # of ways to fill when only the bottom left 2 cells are filled

		// for any function f, f(-ve) = 0

		// f(x) = f(x - 1) + 2 * g(x) + f(x - 3)
		// g(x) = h(x - 2)
		// h(x) = i(x - 2) + h(x - 3)
		// i(x) = f(x - 2) + i(x - 3)
		int mod = int(1e9 + 7);
		vector<ll int> f(max(n + 1, 4), 0), g(max(n + 1, 4), 0), h(max(n + 1, 4), 0), i(max(n + 1, 4), 0);
		f[0] = 1;
		f[1] = 1;
		f[2] = 1;
		f[3] = 2;

		g[0] = 0;
		g[1] = 0;
		g[2] = 0;
		g[3] = 0;

		h[0] = 0;
		h[1] = 0;
		h[2] = 0;
		h[3] = 0;

		i[0] = 0;
		i[1] = 0;
		i[2] = 1;
		i[3] = 1;

		for (int x = 4; x <= n; x++) {
			i[x] = f[x - 2] + i[x - 3];
			i[x] = i[x] % mod;

			h[x] = i[x - 2] + h[x - 3];
			h[x] = h[x] % mod;
			
			g[x] = h[x - 2];
			g[x] = g[x] % mod;
			
			f[x] = f[x - 1] + 2 * g[x] + f[x - 3];
			f[x] = f[x] % mod;

		}

		cout << f[n] << endl;
	}
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int t; cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}