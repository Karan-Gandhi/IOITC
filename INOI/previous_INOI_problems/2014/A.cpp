#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

ll int inf = 1e16;
ll int mod = 20011;
int arr[302][302];
int n, m;
int d;
int dp[302][302][302][2];


int rec(int i, int j, int steps, int last) {
	if (arr[i][j] == 0 || steps > d) return 0;
	if (i >= n || j >= m) return 0;
	if (i == n - 1 && j == m - 1) return 1;

	if (dp[i][j][steps][last] != -1) return dp[i][j][steps][last];

	return dp[i][j][steps][last] = (rec(i + 1, j, last == 0 ? steps + 1 : 1, 0) + rec(i, j + 1, last == 1 ? steps + 1 : 1, 1)) % mod;
}

void solve() {
	cin >> n >> m >> d;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];

			for (int k = 0; k <= d; k++) 
				dp[i][j][k][0] = dp[i][j][k][1] = -1;
		} 

	cout << rec(0, 0, 0, 0) << endl;
}

int main() {
	// int t; cin >> t;
	// while (t--)
	solve();

	return 0;
}