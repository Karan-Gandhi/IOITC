#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

ll int inf = 1e16;
ll int mod = 1e9 + 7;

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<ll int>> distances(n, vector<ll int>(n, inf));

	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		a--;
		b--;
		distances[a][b] = c;
		distances[b][a] = c;
	}

	for (int i = 0; i < n; i++) distances[i][i] = 0;

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
			}
		}
	}

	ll int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans = max(ans, distances[i][j]);
		}
	}

	cout << ans << endl;
}

int main() {
	solve();

	return 0;
}