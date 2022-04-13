#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(ll int i = 0; i < (ll int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}

vector<ll int> ans;
vector<ll int> arr;
vector<ll int> c;
vector<bool> taken;
ll int n;

void rec(int idx) {
	if (idx == n) {
		ll int cur = 0;
		ll int mx = 0;
		for (int i = 0; i < n; i++) {
			if (arr[i] > mx) cur += c[arr[i] - 1];
			mx = max(mx, arr[i]);
			ans[i] = max(ans[i], cur);
		}
		return;
	}

	if (arr[idx] == -1) {
		// try all possibilites
		for (int i = 1; i <= n; i++) {
			if (!taken[i]) {
				taken[i] = 1;
				arr[idx] = i;
				rec(idx + 1);
				arr[idx] = -1;
				taken[i] = 0;
			}
		}
	} else {
		rec(idx + 1);
	}
}

void solve() {
	cin >> n;
	arr.resize(n); for (ll int i = 0; i < n; i++) cin >> arr[i];
	c.resize(n); for (ll int i = 0; i < n; i++) cin >> c[i];
	ans = vector<ll int>(n, 0);
	taken.resize(n + 1);

	for (int i = 0; i < n; i++) {
		if (arr[i] != -1) taken[arr[i]] = 1;
	}

	bool good = 1;
	for (ll int i = 0; i < n; i++) {
		if (arr[i] != -1) good = 0;
	}

	if (good) {
		sort(all(c));
		ll int cur = 0;
		for (ll int i = n - 1; i >= 0; i--) {
			cur += c[i];
			cout << cur << ' ';
		}
		cout << endl;
		return;
	}

	if (n <= 8) {
		rec(0);
		// cout << ans << endl;

		for (auto a : ans) cout << a << ' ';
		cout << endl;
		return;
	}

	map<ll int, bool> done;
	for (ll int i = 0; i < n; i++) {
		if (arr[i] != -1) done[arr[i]] = 1;
	}

	vector<ll int> available;

	for (ll int i = 1; i <= n; i++) {
		if (!done[i]) available.push_back(i);
	}

	ll int cur = 0;
	ll int mx = 0;
	ll int ptr = 0;
	for (ll int i = 0; i < n; i++) {
		if (arr[i] == -1) {
			// cout << pl(available[ptr]) << pl(mx) << endl;
			while (ptr < (int)available.size() && available[ptr] <= mx) ptr++;
			// cout << pl(ptr) << endl;
			if (ptr != (int)available.size()) {
				cur++;
				mx = max(mx, available[ptr]);
				ptr++;
			}
		} else {
			if (mx < arr[i]) {
				mx = max(mx, arr[i]);
				cur++;
			}
		}

		cout << cur << ' ';
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll int T = 1;
	// cin >> T;
	while (T--) 
		solve();

	return 0;
}