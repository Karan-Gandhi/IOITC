#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

struct DSU { // Sorry UFDS
	vector<int> p, s;
	int components;

	void init(int n) {
		p = vector<int>(n);
		iota(all(p), 0);
		s = vector<int>(n, 1);
		components = n;
	}

	int get(int x) {
		return p[x] = (p[x] == x ? x : get(p[x]));
	}

	void unite(int a, int b) {
		a = get(a);
		b = get(b);

		if (a == b) return;

		if (s[a] > s[b]) swap(a, b);

		p[a] = b;
		s[b] += s[a];
		components--;
	}

	bool same_set(int a, int b) {
		return get(a) == get(b);
	}

	int size(int x) {
		return s[get(x)];
	}
};


void solve() {
	int n, m; cin >> n >> m;

	vector<pair<int, pair<int, int>>> edges;

	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		a--, b--;
		edges.emplace_back(c, make_pair(a, b));
	}

	sort(all(edges));
}

int main() {
#ifdef LOCAL
    auto clock_start = chrono::high_resolution_clock::now();
    cout << endl;
#endif

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

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