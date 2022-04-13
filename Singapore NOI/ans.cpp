#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}

void solve() {
	int n; cin >> n;
	vector<pair<pair<ll int, ll int>, int>> arr(n);

	for (int i = 0; i < n; i++) {
		// cin >> arr[i].first >> arr[i].second;
		int a, b; cin >> a >> b;
		arr[i] = make_pair(make_pair(a, b), i);
	}

	string ans(n, '1');
	map<int, vector<pair<int, int>>> y;

	for (int i = 0; i < n; i++) {
		y[arr[i].first.second].push_back(make_pair(arr[i].first.first, arr[i].second));
	}

	for (auto [_, line] : y) {
		if (line.size() > 2) {
			sort(all(line));
			for (int i = 1; i < int(line.size()) - 1; i++) {
				ans[line[i].second] = '0';
			}
		}
	}

	cout << ans << endl;
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