#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}

ll int inf = 1e16;

vector<pair<ll int, ll int>> arr;

void solve() {
	int n; cin >> n;
	arr.resize(n); 
	for (int i = 0; i < n; i++) cin >> arr[i].first;
	for (int i = 0; i < n; i++) cin >> arr[i].second;
	// cout << arr << endl;
	int ans = 1;
	bool good = 1;
	for (int i = 1; i < n; i++) {
		// cout << pl(arr[i].second) << pl(arr[i - 1].second) << pl(good) << endl;
		if (arr[i].second != arr[i - 1].second) good = 0;
	}

	// cout << pl(good) << endl;

	if (good) {
		// cout << "HERE" << endl;
		sort(all(arr));

		llint cur = 0;
		int i;
		for (i = 0; i < n; i++) {
			if (cur <= arr[i].second) {
				cur += arr[i].first;
			} else {
				// ans = max(ans, i+1);
				// if (ans == 5) cout << arr << endl;
				break;
			}
		}
		ans = max(ans, i);
		cout << ans << endl;
		return;
	}

	for (int i = 0; i < n; i++) swap(arr[i].first, arr[i].second);

	sort(all(arr));

	vector<vector<int>> dp(n, vector<int>(n + 1, 0));
	dp[0][1] = arr[0].first;
	dp[0][0] = 0;
	for (int j = 1; j <= n; j++) {
		int mn = dp[0][j - 1];
		for (int i = 1; i < n; i++) {
			if ()
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) 
		solve();

	return 0;
}