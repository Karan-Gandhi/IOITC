#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(ll int i = 0; i < (ll int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}

const ll int LOG = 20;
ll int inf = 1e9;
ll int n, r;
vector<vector<ll int>> jump;
vector<ll int> types;
vector<vector<pair<ll int, ll int>>> adj;
vector<vector<tuple<ll int, ll int, ll int>>> queries;
vector<ll int> ans;
vector<vector<ll int>> nodes_of_type;
vector<ll int> dep, par, node_dist;
vector<vector<ll int>> jumpMin;
int b = 100;

void dfs(ll int u, ll int p) { // root it randomly
	par[u] = p;
	if (u != p) dep[u] = dep[p] + 1;
	for (auto [v, _] : adj[u]) {
		if (v == p) continue;
		node_dist[v] = node_dist[u] + _;
		dfs(v, u);
	}
}

pair<ll int, ll int> kth(ll int u, ll int k, bool ok) {
	ll int pow = LOG - 1;
	ll int res = -1; if (ok) res = jumpMin[u][0];

	while (k > 0) {
		while (k < (1 << pow)) pow--;
		if (ok) res = min(res, jumpMin[u][pow]);
		u = jump[u][pow];
		k -= (1 << pow);
	}
	if (ok) res = min(res, jumpMin[u][0]);

	return make_pair(u, res);
}

pair<ll int, ll int> lca(ll int a, ll int b, bool ok = 1) {
	if (dep[a] < dep[b]) swap(a, b);
	ll int res;
	tie(a, res) = kth(a, dep[a] - dep[b], ok);
	if (ok) res = min(res, jumpMin[b][0]);
	if (a == b) return make_pair(a, res);

	ll int pow = LOG - 1;

	while (pow >= 0) {
		if (jump[a][pow] != jump[b][pow]) {
			if(ok) res = min({res, jumpMin[a][pow], jumpMin[b][pow]});

			a = jump[a][pow];
			b = jump[b][pow];
		}

		pow--;
	}

	assert(jump[a][0] == jump[b][0]);

	if (ok)
		res = min({
			res,
			jumpMin[a][1],
			jumpMin[b][1]
		});
	return make_pair(jump[a][0], res);
}

ll int get_dist(int a, int b) {
	// cout << pl(a) << pl(b) << endl;
	// cout << pl(lca(a, b)) << endl;
	// return 0;
	return node_dist[a] + node_dist[b] - 2 * node_dist[lca(a, b, 0).first];
}

void solve() {
	cin >> n >> r;

	b = sqrt(n);

	types.resize(n);
	adj.resize(n);
	queries.resize(r);
	nodes_of_type.resize(r);
	dep.resize(n);
	par.resize(n);
	node_dist.resize(n);

	for (ll int i = 0; i < n; i++) {
		cin >> types[i];
		types[i]--;
		nodes_of_type[types[i]].push_back(i);
	}

	for (ll int i = 0; i < n - 1; i++) {
		ll int a, b, c; cin >> a >> b >> c;
		a--, b--;
	
		adj[a].emplace_back(b, c);
		adj[b].emplace_back(a, c);
	}

	dfs(0, 0);

	jump = vector<vector<ll int>>(n, vector<ll int>(LOG));
	// cout << pl(par) << endl;
	for (ll int i = 0; i < n; i++) {
		jump[i][0] = par[i];
	}

	for (ll int i = 1; i < LOG; i++) {
		for (ll int j = 0; j < n; j++) {
			jump[j][i] = jump[jump[j][i - 1]][i - 1];
		}
	}

	ll int q; cin >> q;
	ans.resize(q);

	for (ll int i = 0; i < q; i++) {
		ll int a, b, c; cin >> a >> b >> c;

		a--, b--, c--;

		if (nodes_of_type[c].size() > b) queries[c].emplace_back(a, b, i);
		else {
			ans[i] = -1;
			for (int node : nodes_of_type[c]) {
				if (ans[i] == -1) ans[i] = get_dist(a, node) + get_dist(b, node);

				ans[i] = min(ans[i], get_dist(a, node) + get_dist(b, node));
			}
		}
	}

	for (ll int cur_type = 0; cur_type < r; cur_type++) {
		vector<ll int> dist(n, inf);
		priority_queue<pair<ll int, ll int>> q;

		for (ll int j = 0; j < n; j++) {
			if (types[j] == cur_type) {
				dist[j] = 0;
				q.emplace(0, j);
			}
		}

		while (q.size()) {
			auto [d, node] = q.top();
			d = d * -1;
			q.pop();

			if (dist[node] != d) continue;

			for (auto [v, wt] : adj[node]) {
				ll int new_dist = d + wt;

				if (dist[v] > new_dist) {
					dist[v] = new_dist;
					q.emplace(-new_dist, v);
				}
			}
		}

		jumpMin = vector<vector<ll int>>(n, vector<ll int>(LOG));

		for (ll int i = 0; i < n; i++) {
			jumpMin[i][0] = dist[i];
		}

		for (ll int i = 1; i < LOG; i++) {
			for (ll int j = 0; j < n; j++) {
				jumpMin[j][i] = min(jumpMin[j][i - 1], jumpMin[jump[j][i - 1]][i - 1]);
			}
		}

		// now answer queries
		for (auto [a, b, idx] : queries[cur_type]) {
			ll int dd, l;
			tie(l, dd) = lca(a, b);

			ans[idx] = node_dist[a] + node_dist[b] - 2 * node_dist[l] + 2 * dd;
		}
	}

	// cout << ans << endl;
	for (ll int a : ans) {
		cout << a << endl;
	}
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