#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> arr(n);

	for (int i = 0; i < n; i++) cin >> arr[i].first >> arr[i].second;

	vector<int> pref[2], suff[2];
	pref[0] = pref[1] = suff[0] = suff[1] = vector<int>(n + 2);
	pref[0][0] = 1e9;
	suff[0][n - 1] = 1e9;

	for (int i = 1; i <= n; i++) {
		pref[0][i] = min(pref[0][i - 1], arr[i - 1].second);
		pref[1][i] = max(pref[1][i - 1], arr[i - 1].second);
	}

	for (int i = n - 2; i >= 0; i--) {
		suff[0][i] = min(suff[0][i + 1], arr[i + 1].second);
		suff[1][i] = max(suff[1][i + 1], arr[i + 1].second);
	}

	int ans = 1e9;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (i == 0 && j == n - 1) continue;
			int cur = arr[j].first - arr[i].first;

			cur += max(pref[1][i], suff[1][j]) - min(pref[0][i], suff[0][j]);
			ans = min(ans, cur);
		}
	}

	cout << ans << endl;
}

int main() {
#ifdef LOCAL
    auto clock_start = chrono::high_resolution_clock::now();
    cout << endl;
#endif

	// ios::sync_with_stdio(false);
	// cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) 
		solve();

#ifdef LOCAL
    auto clock_end = chrono::high_resolution_clock::now();
    cout << endl;
    chrono::duration<double> elapsed = clock_end - clock_start;
    cout << "Execution time: " << elapsed.count() << "s" << endl;
#endif

	return 0;
}