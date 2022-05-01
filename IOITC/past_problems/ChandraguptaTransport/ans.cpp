#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

struct Seg_tree {
	ll int tree_size, array_size;
	vector<ll int> tree;

	void init(ll int n) {
		array_size = n;
		while (__builtin_popcount(array_size) != 1) array_size++;

		tree_size = 2 * array_size - 1;
		tree.resize(tree_size);
		fill(all(tree), 0);
	}

	void update(ll int idx, ll int val) {
		update_dfs(0, idx, val, 0, array_size - 1);
	}

	void update_dfs(ll int u, ll int idx, ll int val, ll int node_left, ll int node_right) {
		if (node_right == node_left) {
			assert(node_left == idx);

			tree[u] += val;
			return;
		}

		ll int mid = (node_right + node_left) / 2;

		if (idx <= mid) {
			update_dfs(2 * u + 1, idx, val, node_left, mid);
		} else {
			update_dfs(2 * u + 2, idx, val, mid + 1, node_right);
		}

		pull(u);
	}

	ll int query(ll int l, ll int r) {
		return query_dfs(0, l, r, 0, array_size - 1);
	}

	ll int query_dfs(ll int u, ll int q_left, ll int q_right, ll int node_left, ll int node_right) {
		pair<ll int, ll int> q = {q_left, q_right};
		
		if (q_left <= node_left && node_right <= q_right) {
			return tree[u];
		}

		ll int mid = (node_right + node_left) / 2;

		ll int res = 0;

		if (intersects(q, make_pair(node_left, mid))) {
			res += query_dfs(2 * u + 1, q_left, q_right, node_left, mid);
		}

		if (intersects(q, make_pair(mid + 1, node_right))) {
			res += query_dfs(2 * u + 2, q_left, q_right, mid + 1, node_right);
		}

		return res;
	}

	bool intersects(pair<ll int, ll int> a, pair<ll int, ll int> b) {
		if (a.first > b.first) swap(a, b);

		return a.second >= b.first;
	}

	void pull(ll int u) {
		tree[u] = tree[2 * u + 1] + tree[2 * u + 2];
	}
};

vector<vector<ll int>> adj;
vector<tuple<ll int, ll int, ll int>> batch;
vector<ll int> tour, tin, tout, dep;
vector<bool> needs_update;
vector<vector<pair<ll int, ll int>>> updates;
ll int ti = 0;
ll int k = 400;
Seg_tree tree;

void tour_dfs(ll int u, ll int par, ll int _dep = 0) {
	tour.push_back(u);
	tin[u] = ti;
	ti++;
	dep[u] = _dep;

	for (ll int v : adj[u]) {
		if (v == par) continue;

		tour_dfs(v, u, _dep + 1);
	}

	tout[u] = ti;
	tour.push_back(u);
	ti++;
}


bool is_ancestor(ll int u, ll int par) {
	return (tin[par] < tin[u] && tout[u] < tout[par]);
}

ll int dist(ll int u, ll int par) {
	return dep[u] - dep[par] + 1;
}

void batch_update_dfs(ll int u, ll int par, ll int a, ll int d) {
	if (needs_update[u]) {
		needs_update[u] = 0;
		for (auto _update : updates[u]) {
			a += _update.first;
			d += _update.second;			
		}
		updates[u].clear();
	}
	tree.update(tin[u], a);
	tree.update(tout[u], -a);

	for (ll int v : adj[u]) {
		if (v == par) continue;

		batch_update_dfs(v, u, a + d, d);
	}
}

void process_batch() {
	batch_update_dfs(0, 0, 0, 0);
	batch.clear();
}

void update(ll int u, ll int a, ll int d) {
	batch.push_back(make_tuple(u, a, d));
	needs_update[u] = 1;
	updates[u].push_back({a, d});
	if ((ll int)batch.size() >= k) {
		process_batch();
	}
}

ll int query(ll int u) {
	ll int res = tree.query(0, tin[u]);

	for (auto cur_update : batch) {
		ll int v = get<0>(cur_update);
		ll int a = get<1>(cur_update);
		ll int d = get<2>(cur_update);

		if (is_ancestor(u, v) || v == u) {
			ll int len = dist(u, v);

			res += len * (2 * a + (len - 1) * d) / 2;
		}
	}

	return res;
}

void solve() {
	ll int n, q; cin >> n >> q;

	adj.resize(n);
	tin.resize(n);
	tout.resize(n);
	dep.resize(n);
	needs_update.resize(n);
	updates.resize(n);

	for (ll int i = 0; i < n - 1; i++) {
		ll int a, b; cin >> a >> b;

		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	// first create the euler tour
	tour_dfs(0, 0);
	tree.init(ti + 1);

	for (ll int i = 0; i < n; i++) {
		ll int a; cin >> a;
		tree.update(tin[i], a);
		tree.update(tout[i], -a);
	}
	while (q--) {
		ll int type; cin >> type;

		if (type == 1) {
			ll int v, a, d; cin >> v >> a >> d;
			v--;
			update(v, a, d);
		} else {
			ll int u; cin >> u;
			u--;
			cout << query(u) << endl;	
		}
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