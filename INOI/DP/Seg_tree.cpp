struct Seg_tree {
	vector<ll int> tree;
	ll int array_size;
	ll int tree_size;

	void init(ll int n) {
		array_size = n;
		while (__builtin_popcount(array_size) != 1) {
			array_size++;
		}
		tree_size = 2 * array_size - 1;
		tree.resize(tree_size);
		fill(all(tree), 0);
	}

	void pull(ll int u) {
		tree[u] = tree[2 * u + 1] + tree[2 * u + 2];
	}

	void update(ll int idx, ll int val) {
		return update_dfs(0, idx, val, 0, array_size - 1);
	}

	void update_dfs(ll int u, ll int idx, ll int val, ll int node_left, ll int node_right) {
		if (node_right == node_left) {
			assert(idx == node_left);
			tree[u] += val;
			return;
		}

		ll int mid = (node_right + node_left) / 2;

		if (idx <= mid) {
			update_dfs(2 * u + 1, idx, val, node_left, mid);
			pull(u);
		} else {
			update_dfs(2 * u + 2, idx, val, mid + 1, node_right);
			pull(u);
		}
	}

	ll int query(ll int l, ll int r) {
		// sum from x+1 to n
		return query_dfs(0, l, r, 0, array_size - 1);
	}

	ll int query_dfs(ll int u, ll int q_left, ll int q_right, ll int node_left, ll int node_right) {
		pair<ll int, ll int> q = make_pair(q_left, q_right);
		if (!intersects(q, make_pair(node_left, node_right))) return 0;

		if (q_left <= node_left && node_right <= q_right) {
			return tree[u];
		}

		int mid = (node_right + node_left) / 2;
		ll int res = 0;

		if (intersects(q, make_pair(node_left, mid))) {
			res += query_dfs(2 * u + 1, q_left, q_right, node_left, mid);
		} if (intersects(q, make_pair(mid + 1, node_right))) {
			res += query_dfs(2 * u + 2, q_left, q_right, mid + 1, node_right);
		}

		return res;
	}

	bool intersects(pair<ll int, ll int> a, pair<ll int, ll int> b) {
		if (a.first > b.first) swap(a, b);

		return a.second >= b.first;
	}

	void print() {
		cout << " [";
		for (int i = 0; i < array_size; i++) {
			cout << tree[array_size + i - 1] << ' ';
		}
		cout << "] " << endl;
	}
};