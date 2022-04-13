#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

ll int inf = 1e16;
ll int mod = 20011;
int n, m, c;
vector<vector<bool>> arr;
int dp[310][310][310][3];

ll int rec(int x, int y, int cur, int last) {
	if (x >= n || y >= m || cur > c || !arr[x][y]) {
		return 0;
	}
	// cout << pl(x) << pl(y) << pl(cur) << pl(last) << endl;
	if (x == n - 1 && y == m - 1) {
		return 1;
	}

	if (dp[x][y][cur][last] != -1) {
		return dp[x][y][cur][last];
	}
	ll int res = 0;
	if (last == 1) {
		res += rec(x + 1, y, 1, 0);
		res += rec(x, y + 1, cur + 1, 1);
	} else {
		res += rec(x + 1, y, cur + 1, 0);
		res += rec(x, y + 1, 1, 1);
	}

	res %= mod;

	return dp[x][y][cur][last] = res;
}

void solve() {
	cin >> n >> m >> c;
	memset(dp, -1, sizeof dp);
	arr = vector<vector<bool>>(n + 1, vector<bool>(m + 1));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int a; cin >> a;
			arr[i][j] = a;
		}
	}

	cout << rec(0, 0, 0, 0) << endl;
}

int main() {
	solve();

	return 0;
}