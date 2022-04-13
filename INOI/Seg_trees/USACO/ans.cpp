#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

struct Seg_tree {
	int array_size;
	vector<ll int> tree;
	int tree_size;

	void init(vector<int> arr) {
		int n = arr.size();
		while (__builtin_popcount(n) != 1) n++;
		array_size = n;
		tree_size = 2 * n - 1;
		n = arr.size();
		tree.resize(tree_size);

		for (int i = 0; i < n; i++) {
			tree[array_size + i - 1] = arr[i];
		}

		for (int i = array_size - 2; i >= 0; i--) {
			pull(i);
		}
	}

	void pull(int u) {
		assert(u < tree_size);
		tree[u] = cmp(tree[2 * u + 1], tree[2 * u + 2]);
	}

	ll int cmp(ll int a, ll int b) {
		return a + b;
	}

	void set_val(int idx, ll int val) {
		set_val_dfs(0, idx, val, 0, array_size - 1);
	}

	void set_val_dfs(int u, int idx, ll int val, int node_left, int node_right) {
		if (u >= tree_size) return;
		if (node_left == node_right) {
			assert(idx == node_right);
			tree[u] = val;
			return;
		}

		int mid = (node_left + node_right) / 2;

		if (idx <= mid) {
			set_val_dfs(2 * u + 1, idx, val, node_left, mid);
			pull(u);
		} else {
			set_val_dfs(2 * u + 2, idx, val, mid + 1, node_right);
			pull(u);
		}
	}

	ll int query(int idx) {
		// return the id of the hotel having the value more than val
		return query_dfs(0, idx, 0, 0, array_size - 1);
	}

	ll int query_dfs(int u, int idx, int suff, int node_left, int node_right) {
		if (u >= tree_size) return -1;

		if (node_left == node_right) {
			// return this element
			assert(idx == node_right);
			return suff;
		}

		int mid = (node_left + node_right) / 2;

		if (idx <= mid) {
			return query_dfs(2 * u + 1, idx, suff + tree[2 * u + 2], node_left, mid);
		} else {
			return query_dfs(2 * u + 2, idx, suff, mid + 1, node_right);
		}
	}
};

void solve() {
	int n; cin >> n;
	vector<int> arr(n); for (int i = 0; i < n; i++) cin >> arr[i];
	vector<int> dup = arr;
	sort(all(arr));
	map<int, int> idx;
	for (int i = 0; i < n; i++) idx[dup[i]] = i;

	for (int i = 0; i < n; i++) arr[i] = idx[arr[i]];

	Seg_tree tree;
	tree.init(vector<int>(n, 0));

	ll int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += tree.query(arr[i]);
		tree.set_val(arr[i], 1);
	}

	cout << ans << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	// solve();
	int t; cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}