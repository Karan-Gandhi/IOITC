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
	vector<pair<ll int, ll int>> arr(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}

	vector<bool> done(n, 0);
	// vector<vector<pair<int, int>>> x, y;
	map<int, vector<pair<int, int>>> x, y;

	for (int i = 0; i < n; i++) {
		x[arr[i].first].push_back({arr[i].second, i});
		y[arr[i].second].push_back({arr[i].first, i});
	}
	string ans(n, '0');

	for (auto [_, line] : y) {
		sort(all(line));
		ans[line[0].second] = '1';
		ans[line[int(line.size()) - 1].second] = '1';

		for (int i = 0; i < int(line.size()); i++) {
			done[line[i].second] = 1;
		}
	}

	for (auto [_, line] : x) {
		int start = 0;
		sort(all(line));

		while (done[line[start].second] && start < int(line.size())) start++;
		if (start == line.size()) continue;
		
		int end = line.size();
		end--;

		while (done[line[end].second] && end >= 0) end--;
		if (end == -1) assert(0);
		assert(start - 1 != end);
		ans[line[start].second] = '1';
		ans[line[end].second] = '1';

		for (int i = start; i < end; i++) {
			done[i] = 1;
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