// sqrt + dynamic lca!!

#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

vector<vector<int>> adj;
int n = 0;
int b = 320;
vector<int> roots;
vector<int> updates;
vector<vector<int>> jump; // ouch!
vector<int> dp1, dp2, dep;
const int LOG = 20;
int process_batch_cnt = 0;
int query_cnt = 0;
int update_cnt = 0;

int kth(int u, int k) {
	int pow = LOG;

	while (k > 0) {
		while (k < (1 << pow)) pow--;

		u = jump[u][pow];
		k -= (1 << pow);
	}

	return u;
}

int lca(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	a = kth(a, dep[a] - dep[b]);
	assert(dep[a] == dep[b]);
	if (a == b) return a;

	int pow = LOG;

	while (pow >= 0) {
		if (jump[a][pow] != jump[b][pow]) {
			a = jump[a][pow];
			b = jump[b][pow];
		}
		pow--;
	}

	if (jump[a][0] != jump[b][0]) {
		return -1;
	}
	// assert(jump[a][0] == jump[b][0]);
	return jump[a][0];
}

int dist(int a, int b) {
	int l = lca(a, b);
	if (l == -1) return -1;
	return dep[a] + dep[b] - 2 * dep[l];
}

void dfs(int u) {
	dp1[u] = 0;
	for (int v : adj[u]) {
		dfs(v);

		dp1[u] = max(dp1[u], dp1[v] + 1);
	}
}

void dfs2(int u) {
	int best1 = -1;
	int best2 = -1;

	for (int v : adj[u]) {
		if (best1 == -1) best1 = v;
		if (dp1[best1] < dp1[v]) best1 = v;
	}

	for (int v : adj[u]) {
		if (v == best1) continue;
		
		dp2[v] = max(dp1[best1] + 2, dp2[u] + 1);

		if (best2 == -1) best2 = v;
		if (dp1[best2] < dp1[v]) best2 = v;
	}

	if (best2 != -1) dp2[best1] = max(dp1[best2] + 2, dp2[u] + 1);
	else if (best1 != -1) dp2[best1] = dp2[u] + 1;

	for (int v : adj[u]) dfs2(v);	
}

void process_batch() {
	process_batch_cnt++;
	for (int root : roots) dfs(root);
	for (int root : roots) dfs2(root);
	updates.clear();
}

int query(int u) {
	query_cnt++;
	int res = max(dp2[u], dp1[u]);

	for (int node : updates) {
		res = max(res, dist(node, u));
	}

	return res;
}

void update(int node, int p) {
	update_cnt++;
	adj[p].push_back(node);
	dep[node] = dep[p] + 1;

	jump[node][0] = p;

	for (int i = 1; i < LOG; i++) {
		jump[node][i] = jump[jump[node][i - 1]][i - 1];
	}

	dp2[node] = max(dp2[p], dp1[p]) + 1;

	updates.push_back(node);

	if ((int) updates.size() > b) process_batch();
}

void solve() {
	// sqrt + dynamic lca
	int q; cin >> q;

	adj.resize(q); // there will be atmost q nodes
	dp1.resize(q);
	dp2.resize(q);
	dep.resize(q);

	jump = vector<vector<int>>(q, vector<int>(LOG));

	while (q--) {
		char c; cin >> c;
		if (c == 'B') {
			// build a farm
			int a; cin >> a;
			if (a == -1) {
				roots.push_back(n);
				updates.push_back(n);
				dep[n] = 0;
				jump[n][0] = n;
				n++;
				continue;
			}

			a--;

			update(n, a); // attach node n to a
			n++;
		} else {
			// query
			int a; cin >> a;
			a--;
			cout << query(a) << endl;
		}
	}
}

int main() {
	// freopen("newbarn.in", "r", stdin);
	// freopen("newbarn.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--)
		solve();
}