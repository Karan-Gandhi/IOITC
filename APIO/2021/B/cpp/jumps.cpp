#include "jumps.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

int n;
vector<int> h;
vector<vector<int>> adj;
const int LOG = 20;
vector<vector<int>> hi, lo;

void init(int N, std::vector<int> H) {
	n = N;
	h = H;
	adj.resize(n);

	hi = vector<vector<int>>(n, vector<int>(LOG));
	lo = vector<vector<int>>(n, vector<int>(LOG));

	stack<int> st;
	for (int i = 0; i < n; i++) {
		// cout << st.size() << endl;
		while (st.size() > 0 && h[st.top()] < h[i]) {
			st.pop();
		}
		if (st.size() != 0) adj[i].push_back(st.top());
		st.push(i);
	}

	while (st.size() != 0) st.pop();
	
	for (int i = n - 1; i >= 0; i--) {
		while (st.size() > 0 && h[st.top()] < h[i]) {
			st.pop();
		}
		if (st.size() != 0) adj[i].push_back(st.top());
		st.push(i);
	}

	// first build the lo
	for (int i = 0; i < n; i++) {
		if (adj[i].size() == 0) {
			lo[i][0] = -1;
			continue;
		}
		int nxt = adj[i][0];
		for (int v : adj[i]) if (h[nxt] > h[v]) nxt = v;
		lo[i][0] = nxt;
	}

	for (int i = 1; i < LOG; i++) {
		for (int j = 0; j < n; j++) {
			if (lo[j][i - 1] == -1) {
				lo[j][i] = -1;
				continue;
			}
			lo[j][i] = lo[lo[j][i - 1]][i - 1];
		}
	}

	for (int i = 0; i < n; i++) {
		if (adj[i].size() == 0) {
			hi[i][0] = -1;
			continue;
		}
		int nxt = adj[i][0];
		for (int v : adj[i]) if (h[nxt] < h[v]) nxt = v;
		hi[i][0] = nxt;
	}

	for (int i = 1; i < LOG; i++) {
		for (int j = 0; j < n; j++) {
			if (hi[j][i - 1] == -1) {
				hi[j][i] = -1;
				continue;
			}
			hi[j][i] = hi[hi[j][i - 1]][i - 1];
		}
	}
}

int minimum_jumps(int a, int b, int c, int d) {

	if (a == b && c == d) {		
		int pow = LOG - 1;
		int u = a;
		int t = c;
		ll int ans = 0;
		while (pow >= 0) {
			if (hi[u][pow] != -1 && h[hi[u][pow]] <= h[t]) {
				u = hi[u][pow]; // keep taking the hi edge
				ans += (1 << pow);
			}
			if (h[u] == h[t]) return ans;
			pow--;
		}

		pow = LOG - 1;

		while (pow >= 0) {
			if (lo[u][pow] != -1 && h[lo[u][pow]] <= h[t]) {
				u = lo[u][pow];
				ans += (1 << pow);
			}
			if (u == t) return ans;
			pow--;
		}
		// if (lo[u][0] != t) return -1;

		return -1;
	} else {
		int res = 1e6;
 
		queue<pair<int, int>> nodes;
		
		for (int start = a; start <= b; start++) {
			nodes.emplace(start, 0);
		}
	 
		vector<bool> vis(n, 0);
		// cout << pl(adj[4]) << endl;
	 
		while (nodes.size() > 0) {
			auto [cur_node, dist] = nodes.front();
			nodes.pop();
	 
			if (vis[cur_node]) continue;
			vis[cur_node] = 1;
			// cout << pl(cur_node) << pl(dist) << endl;
	 
			if (c <= cur_node && cur_node <= d) {
				res = min(res, dist);
				break;
			}
	 
			for (int v : adj[cur_node]) {
				nodes.emplace(v, dist + 1);
			}
		}
	 
		if (res == 1e6) return -1;
	 
		return res;
	}
}
