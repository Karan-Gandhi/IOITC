#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

void solve() {
	int n; cin >> n;
	int s = 0;
	vector<int> arr(n); for (int i = 0; i < n; i++) cin >> arr[i];
	for (int i = 0; i < n; i++) s += arr[i];
	vector<bool> dp

	vector<int> ans;

	for (int i = 1; i <= s; i++) {
		if (dp[i][n - 1]) {
			ans.push_back(i);
		}
	}

	cout << ans.size() << endl;
	for (auto a : ans) cout << a << ' ';
	cout << endl;
}

int main() {
	// cin.tie(nullptr);
	// ios::sync_with_stdio(false);

	solve();

	return 0;
}