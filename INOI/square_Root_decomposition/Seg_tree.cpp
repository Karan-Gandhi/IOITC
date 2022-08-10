struct Seg_tree {
	vector<ll int> tree;
	int array_size;
	int tree_size;

	ll int def = 0;

	void init(int n) {
		array_size = n;
		while (__builtin_popcount(array_size) != 1) {
			array_size++;
		}
		tree_size = 2 * array_size - 1;
		tree = vector<ll int>(tree_size, def);
	}

	void comb(ll int a, ll int b) {
		return a + b;
	}

	void pull(int u) {
		tree[u] = comb(tree[2 * u + 1], tree[2 * u + 2]);
	}

	void update(int idx, ll int val) {
		return update_dfs(0, idx, val, 0, array_size - 1);
	}

	void update_dfs(int u, int idx, ll int val, int node_left, int node_right) {
		if (node_right == node_left) {
			assert(idx == node_left);
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

	ll int query(int l, int r) {
		// sum from x+1 to n
		return query_dfs(0, l, r, 0, array_size - 1);
	}

	ll int query_dfs(int u, int q_left, int q_right, int node_left, int node_right) {
		pair<int, int> q = make_pair(q_left, q_right);
		if (!intersects(q, make_pair(node_left, node_right))) return 0;

		if (q_left <= node_left && node_right <= q_right) {
			return tree[u];
		}

		int mid = (node_right + node_left) / 2;
		ll int res = def;

		if (intersects(q, make_pair(node_left, mid))) {
			res = comb(res, query_dfs(2 * u + 1, q_left, q_right, node_left, mid));
		} if (intersects(q, make_pair(mid + 1, node_right))) {
			res = comb(res, query_dfs(2 * u + 2, q_left, q_right, mid + 1, node_right));
		}

		return res;
	}

	bool intersects(pair<int, int> a, pair<int, int> b) {
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