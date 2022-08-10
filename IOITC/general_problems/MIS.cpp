#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

string bin(int ans) {
	string res = "";

	while (ans > 0) {
		res += (ans % 2) + '0';
		ans /= 2;
	}

	while (res.size() != 8) res += '0';

	reverse(all(res));

	return res;
}

void solve() {
	int n, m; cin >> n >> m;

	vector<vector<bool>> is_edge(n, vector<bool>(n, 1));

	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;

	// 	a--, b--;
		is_edge[a][b] = 0;
		is_edge[b][a] = 0;
	}

	// dp[mask] = dp[mask ^ bit]
	vector<int> dp(1 << n, 0); for (int i = 0; i < n; i++) dp[1 << i] = (1 << i);
	vector<int> neighbours(n); // mask representing the neighbours

	for (int i = 0; i < n; i++) {
		int res = 0;
		for (int j = 0; j < n; j++) {
			if (is_edge[i][j] && i != j) res |= (1 << j);
		}
		neighbours[i] = res;
	}

	for (int n : neighbours) {
		cout << bin(n) << ' ';
	}
	cout << endl;

	auto popMax = [&](int a, int b) {
		return __builtin_popcount(a) < __builtin_popcount(b) ? b : a;
	};

	int ans = 0;
	for (int subset = 0; subset < (1 << n); subset++) {
		for (int bit = 0; bit < n; bit++) {
			if (subset & (1 << bit)) {
				dp[subset] = popMax(dp[subset ^ (1 << bit)], 
									dp[subset & neighbours[bit]] | (1 << bit));
				cout << pl(bin(subset)) << pl(bin(dp[subset ^ (1 << bit)])) << pl(bin(dp[subset & neighbours[bit]] | (1 << bit))) << endl;
				ans = popMax(ans, dp[subset]);
				break;
			}
		}
	}

	cout << bin(dp[(1 << n) - 1]) << endl;

	// cout << dp[(1 << n) - 1] << endl;

	cout << __builtin_popcount(ans) << endl;
}

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--)
		solve();
}