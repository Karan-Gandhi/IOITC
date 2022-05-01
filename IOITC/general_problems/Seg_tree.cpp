struct Seg_tree {
	vector<ll int> tree;
	ll int tree_size;
	ll int array_size;

	void init(ll int n) {
		array_size = n;
		while (__builtin_popcount(array_size) != 1) {
			array_size++;
		}

		tree_size = 2 * array_size - 1;

		tree = vector<ll int>(tree_size, 0);
	}

	void update(ll int idx, ll int val) {
		update_dfs(0, idx, val, 0, array_size - 1);
	}

	void update_dfs(ll int u, ll int idx, ll int val, ll int node_left, ll int node_right) {
		if (node_right == node_left) {
			// cout << pl(node_right) << pl(idx) << endl;
			assert(node_right == idx);
			// if (node_right != idx) exit(0);
			tree[u] = val;
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

	bool intersects(pair<ll int, ll int> a, pair<ll int, ll int> b) {
		if (a.first > b.first) swap(a, b);
		return a.second >= b.first;
	}

	ll int query_dfs(ll int u, ll int q_left, ll int q_right, ll int node_left, ll int node_right) {
		// cout << pl(u) << pl(q_left) << pl(q_right) << pl(node_left) << pl(node_right) << endl;

		if (q_left <= node_left && node_right <= q_right) {
			return tree[u];
		}


		pair<ll int, ll int> q = make_pair(q_left, q_right);
		ll int mid = (node_right + node_left) / 2;

		ll int res = 0;
		if (intersects(q, {node_left, mid})) {
			res += query_dfs(2 * u + 1, q_left, q_right, node_left, mid);
		} 
		if (intersects(q, {mid + 1, node_right})) {
			res += query_dfs(2 * u + 2, q_left, q_right, mid + 1, node_right);
		}

		return res;
	}

	void pull(ll int u) {
		tree[u] = tree[2 * u + 1] + tree[2 * u + 2];
	}
};