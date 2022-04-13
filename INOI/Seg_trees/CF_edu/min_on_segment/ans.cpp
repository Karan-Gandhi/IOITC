#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

struct Seg_tree {
	vector<pair<int64_t, int64_t>> arr;
	vector<pair<int64_t, int64_t>> tree; // {min, number of min's}
	int array_size;
	int tree_size;

	void init(int n, vector<pair<int64_t, int64_t>>& _arr) {
		assert(__builtin_popcount(n) == 1);
		array_size = n;
		arr = _arr;
		tree_size = 2 * n - 1;
		tree.resize(tree_size);

		for (int i = 0; i < n; i++) {
			tree[n + i - 1] = arr[i];
		}

		init_dfs(0);
		// pt();
	}

	void pull(int u) {
		assert(u < tree_size);
		auto l = tree[2 * u + 1];
		auto r = tree[2 * u + 2];

		if (l.first < r.first) {
			tree[u] = l;
		} else if (r.first < l.first) {
			tree[u] = r;
		} else if (r.first == l.first) {
			tree[u] = make_pair(r.first, l.second + r.second);
		}
	}

	void pt() {
		for (int i = 0; i < tree_size; i++) {
			cout << pl(i) << pl(tree[i].first) << pl(tree[i].second) << endl;
		}
	}

	void init_dfs(int u) {
		if (u >= tree_size) return;
		if (2 * u + 2 >= tree_size) return;

		init_dfs(2 * u + 1);
		init_dfs(2 * u + 2);
		pull(u);
	}

	bool intersects(pair<int, int> a, pair<int, int> b) {
		if (a.first > b.first) swap(a, b);
		if (a.second < b.first) return 0;
		return 1;
	}

	void set_val(int idx, int val) {
		set_val_dfs(0, idx, val, 0, array_size - 1);
	}

	void set_val_dfs(int u, int idx, int val, int node_left, int node_right) {
		if (u >= tree_size) return;

		if (!intersects({idx, idx}, {node_left, node_right})) return;

		if (node_right == node_left) {
			assert(node_right == idx);

			tree[u] = {val, 1};
			return;
		}

		int mid = (node_right + node_left) / 2;
		if (idx <= mid) {
			set_val_dfs(2 * u + 1, idx, val, node_left, mid);
			pull(u);
		} else {
			set_val_dfs(2 * u + 2, idx, val, mid + 1, node_right);
			pull(u);
		}
	}

	pair<int64_t, int64_t> get_val(int l, int r) {
		return get_val_dfs(0, l, r, 0, array_size - 1);
	}

	pair<int64_t, int64_t> get_val_dfs(int u, int q_left, int q_right, int node_left, int node_right) {
		if (u >= tree_size) return make_pair(1e10, 0);
		pair<int, int> q = {q_left, q_right};
		if (!intersects(q, {node_left, node_right})) assert(0);
		if (q_left <= node_left && q_right >= node_right) return tree[u];

		int mid = (node_right + node_left) / 2;

		pair<int64_t, int64_t> res = make_pair(1e10, 0);
		bool ok = 0;
		if (intersects(q, {node_left, mid})) {
			ok = 1;
			auto nres = get_val_dfs(2 * u + 1, q_left, q_right, node_left, mid);
			if (nres.first < res.first) {
				res = nres;
			} else if (nres.first == res.first) {
				res.second += nres.second;
			}
		}

		if (intersects(q, {mid + 1, node_right})) {
			ok = 1;
			auto nres = get_val_dfs(2 * u + 2, q_left, q_right, mid + 1, node_right);
			if (nres.first < res.first) {
				res = nres;
			} else if (nres.first == res.first) {
				res.second += nres.second;
			}
		}

		assert(ok);

		return res;
	}
};

void solve() {
	int n, m; cin >> n >> m;
	int on = n;
	vector<pair<int64_t, int64_t>> arr(n); for (int i = 0; i < n; i++) {
		int a; cin >> a;
		arr[i] = {a, 1};
	}
	
	while (__builtin_popcount(n) != 1) {
		arr.emplace_back(1e10, 0);
		n++;
	}

	Seg_tree tree;
	tree.init(n, arr);

	while (m--) {
		int s; cin >> s;
		if (s == 1) {
			int i, val; cin >> i >> val;
			tree.set_val(i, val);
		} else {
			int l, r; cin >> l >> r;
			r--;
			auto res = tree.get_val(l, r);
			cout << res.first << ' ' << res.second << endl;
			// assert(res.first < 1e10);
			// assert(r < on);
		}
	}
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}