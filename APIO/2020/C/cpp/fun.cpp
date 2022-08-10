#include "fun.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

std::vector<int> createFunTour(int n, int Q) {
	vector<vector<pair<int, int>>> distances(n);

	int diameter = 0;
	int a, b;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int d = hoursRequired(i, j);
			if (d > diameter) {
				a = i;
				b = j;
				diameter = d;
			}
			distances[i].emplace_back(d, j);
			distances[j].emplace_back(d, i);
		}
	}

	vector<int> ans;
	ans.push_back(b);
	ans.push_back(a);
	int u = a;

	for (int i = 0; i < n; i++) {
		sort(all(distances[i]));
		reverse(all(distances[i]));
	}

	vector<bool> vis(n, 0);
	vis[a] = vis[b] = 1;
	while (ans.size() != n) {
		for (auto [d, v] : distances[u]) {
			if (!vis[v]) {
				ans.push_back(v);
				vis[v] = 1;
				u = v;
				break;
			}
		}
	}

	assert(ans.size() == n);
	// cout << ans << endl;
	return ans;
}
