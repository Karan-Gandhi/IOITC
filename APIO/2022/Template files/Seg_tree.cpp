using T = ll int;
struct Seg_tree {
	vector<T> tree;
	int array_size;
	int tree_size;

	T def = 0;

	void init(int n) {
		array_size = n;
		while (__builtin_popcount(array_size) != 1) {
			array_size++;
		}

		tree_size = 2 * array_size - 1;
		tree = vector<T>(tree_size, def);
	}

	T comb(T a, T b) {
		return a + b;
	}

	void pull(int u) {
		tree[u] = comb(tree[2 * u + 1], tree[2 * u + 2]);
	}

	void update(int idx, T val) {
		return update_dfs(0, idx, val, 0, array_size - 1);
	}

	void update_dfs(int u, int idx, T val, int node_left, int node_right) {
		if (node_right == node_left) {
			assert(idx == node_left);
			tree[u] = val;
			return;
		}

		int mid = (node_right + node_left) / 2;

		if (idx <= mid) {
			update_dfs(2 * u + 1, idx, val, node_left, mid);
		} else {
			update_dfs(2 * u + 2, idx, val, mid + 1, node_right);
		}
		pull(u);
	}

	T query(int l, int r) {
		// sum from x+1 to n
		return query_dfs(0, l, r, 0, array_size - 1);
	}

	T query_dfs(int u, int q_left, int q_right, int node_left, int node_right) {
		pair<int, int> q = make_pair(q_left, q_right);

		if (q_left <= node_left && node_right <= q_right) {
			return tree[u];
		}

		int mid = (node_right + node_left) / 2;
		T res = def;

		if (intersects(q, make_pair(node_left, mid))) {
			res = comb(query_dfs(2 * u + 1, q_left, q_right, node_left, mid), res);
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