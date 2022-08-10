#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

// template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
// template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(ll ll int i = 0; i < (ll ll int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}

void solve() {
	ll int n; cin >> n;
	vector<ll int> arr(n);

	for (ll int i = 0; i < n; i++) cin >> arr[i];

	// {
	// 	ll int ans = 0;

	// 	for (ll int i = 0; i < n; i++) {
	// 		ll int mn = arr[i];
	// 		for (ll int j = i; j < n; j++) {
	// 			mn = min(arr[j], mn);
	// 			ans += mn;
	// 		}
	// 	}
	// 	cout << ans << endl;
	// }

	vector<ll int> l(n), r(n);

	stack<pair<ll int, ll int>> st;

	for (ll int i = 0; i < n; i++) {
		ll int lc = 1;

		while (st.size() != 0 && st.top().first > arr[i]) {
			lc += st.top().second;
			st.pop();
		}

		st.push(make_pair(arr[i], lc));
		l[i] = lc;
	}

	while (st.size() != 0) st.pop();

	for (ll int i = n - 1; i >= 0; i--) {
		ll int rc = 1;

		while (st.size() != 0 && st.top().first >= arr[i]) {
			rc += st.top().second;
			st.pop();
			// cout << pl(rc) << endl;
		}

		st.push(make_pair(arr[i], rc));
		r[i] = rc;
	}

	ll int ans = 0;

	for (ll int i = 0; i < n; i++) {
		ans += arr[i] * l[i] * r[i];
		// cout << pl(i) << pl(r[i]) << pl(l[i]) << endl;
	}

	cout << ans << endl;
}

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll int T = 1;
	// cin >> T;
	while (T--)
		solve();
}