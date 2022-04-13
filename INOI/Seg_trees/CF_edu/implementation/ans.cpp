#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

struct Seg_tree {
	vector<int64_t> arr;
	int tree_size;
	int array_size;
	vector<int64_t> tree;

	void init(int n, vector<int64_t> _arr) {
		assert(__builtin_popcount(n) == 1);
		arr = _arr;
		array_size = n;
		tree_size = 2 * n - 1;

		tree.resize(tree_size);

		for (int i = 0; i < n; i++) {
			tree[n + i - 1] = arr[i];
		}

		init_dfs(0);
	}

	void pt() {
		for (int i = 0; i < tree_size; i++) {
			cout << pl(tree[i]) << pl(i) << endl;
		}
	}

	void set_val(int idx, int val) {
		set_val_dfs(0, idx, val, 0, array_size - 1);
	}

	int64_t get_val(int l, int r) {
		return get_val_dfs(0, l, r, 0, array_size - 1);
	}

	void init_dfs(int u) {
		if (u >= tree_size) return;
		if (2 * u + 2 >= tree_size) return;

		init_dfs(2 * u + 1);
		init_dfs(2 * u + 2);
		pull(u);
	}

	bool intersects(pair<int, int> a, pair<int, int> b) {
		if (b.first < a.first) swap(a, b);
		if (a.second < b.first) return 0;
		return 1;
	}

	int64_t get_val_dfs(int u, int q_left, int q_right, int node_left, int node_right) {
		pair<int, int> q = make_pair(q_left, q_right);
		if (!intersects(q, make_pair(node_left, node_right))) {
			return 0;
		}

		if (u >= tree_size) return 0;

		if (q_left <= node_left && q_right >= node_right) return tree[u];

		int mid = (node_right + node_left) / 2;

		int64_t res = 1e10;
		if (intersects(q, make_pair(node_left, mid))) {
			res = min(get_val_dfs(2 * u + 1, q_left, q_right, node_left, mid), res);
		}

		if (intersects(q, make_pair(mid + 1, node_right))) {
			res = min(get_val_dfs(2 * u + 2, q_left, q_right, mid + 1, node_right), res);
		}

		return res;
	}

	void set_val_dfs(int u, int idx, int val, int node_left, int node_right) {
		if (u >= tree_size) return;
		if (!intersects(make_pair(idx, idx), make_pair(node_left, node_right))) return;
		if (node_right == node_left) {
			assert(idx == node_left);
			tree[u] = val;
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

	void pull(int u) {
		assert(u < tree_size);
		// tree[u] = tree[2 * u + 1] + tree[2 * u + 2];
		tree[u] = min(tree[2 * u + 1], tree[2 * u + 2]);
	}
};

void solve() {
	int n, m; cin >> n >> m;
	vector<int64_t> arr(n); for (int i = 0; i < n; i++) cin >> arr[i];
	while (__builtin_popcount(n) != 1) {
		arr.push_back(0);
		n++;
	}

	Seg_tree tree;
	tree.init(n, arr);

	while (m--) {
		int s; cin >> s;
		if (s == 1) {
			int i; cin >> i;
			int val; cin >> val;
			tree.set_val(i, val);
		} else {
			int l, r; cin >> l >> r;
			r--;
			cout << tree.get_val(l, r) << endl;
		}
	}
}

int main() {
	// cin.tie(nullptr);
	// ios::sync_with_stdio(false);

	solve();

	return 0;
}