#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

struct DSU {
	vector<int> p, s;

	void init(int n) {
		p = vector<int>(n);
		s = vector<int>(n, 1);
		iota(all(p), 0);
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
	}

	bool same_set(int a, int b) {
		return get(a) == get(b);
	}
}

void solve() {
	int n; cin >> n;
	DSU f; 
	f.init(n + 1);
	// e.init(n + 1);

	while (1) {
		int c; cin >> c;
		if (c == 0) break;
		int x, y; cin >> x >> y;

		if (c == 1) {
			// setFriends
		} else if (c == 2) {
			// setEnemies
		} else if (c == 3) {
			// areFriends
		} else if (c == 4) {
			// areEnemies
		} else assert(0);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// int t; cin >> t;
	// while (t--)
		solve();

	return 0;
}