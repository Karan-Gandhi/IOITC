#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}

ll int dist(pair<ll int, ll int> a) {
	return (a.first * a.first) + (a.second * a.second);
}

pair<ll int, ll int> operator-(const pair<ll int, ll int>& l, const pair<ll int, ll int>& r) {
	return make_pair(l.first - r.first, l.second - r.second);
}

ll int cross(pair<int, int> a, pair<int, int> b) {
	return a.first * b.second - a.second * b.first;
}

void solve() {
	int n; cin >> n;
	vector<pair<ll int, ll int>> arr(n);
	for (int i = 0; i < n; i++) {
		ll int a, b; cin >> a >> b;
		arr[i] = make_pair(a, b);
	}

	int idx = (min_element(all(arr)) - arr.begin());
	vector<int> pts, hull;
	hull.push_back(idx);

	for (int i = 0; i < n; i++) {
		if (i == idx) continue;
		pts.push_back(i);
	}

	sort(all(pts), [&] (int a, int b) {
		pair<ll int, ll int> x = arr[a] - arr[idx];
		pair<ll int, ll int> y = arr[b] - arr[idx];
		ll int c = cross(x, y);

		return c != 0 ? c > 0 : dist(x) < dist(y);
	});

	for (int pt : pts) {
		while (hull.size() > 1 && cross(
			arr[ hull[int(hull.size()) - 1] ] - arr[ hull[int(hull.size()) - 2] ],
			arr[ pt ] - arr[ hull[int(hull.size()) - 2] ]
		) <= 0) {
			hull.pop_back();
		}

		hull.push_back(pt);
	}

	string ans(n, '0');

	for (int a : hull) {
		ans[a] = '1';
	}

	// now check if atleast 2 points are there one a given row or column

	// coordinate compression? or map?

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