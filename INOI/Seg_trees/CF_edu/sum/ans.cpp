#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

//                 0
// 				1        2
//           3     4   5        6
//         7   8 9  10 11 12   13 14

vector<int64_t> segtree;

void init_dfs(int64_t u) {
	if (u >= (int64_t)segtree.size()) return;
	if (2 * u + 2 >= int64_t (segtree.size())) return;
	if ((2 * u + 1) < int64_t(segtree.size())) {
		init_dfs(2 * u + 1);
		init_dfs(2 * u + 2);
		segtree[u] = segtree[2 * u + 1] + segtree[2 * u + 2];
	}
}

void set_val(int64_t u, int64_t idx, int64_t val, int64_t node_left, int64_t node_right) {
	if (u >= (int64_t) segtree.size()) return;
	if (idx < node_left) return;
	if (idx > node_right) return;

	if (node_right == node_left) {
		segtree[u] = val;
		assert(idx == node_left);
		return;
	}

	// range of idx that this containes
	// split this in half
	// [node_left, mid] [mid + 1, node_right] ??

	int64_t mid = (node_right + node_left) / 2;
	if (idx <= mid) {
		// go left
		set_val(2 * u + 1, idx, val, node_left, mid);
		segtree[u] = segtree[2 * u + 1] + segtree[2 * u + 2];
	} else {
		set_val(2 * u + 2, idx, val, mid + 1, node_right);
		segtree[u] = segtree[2 * u + 1] + segtree[2 * u + 2];
	}
}

int64_t init(int64_t n, vector<int64_t>& arr) {
	int64_t segtree_size = 1;
	// find the smallest power of 2 that is more than n
	while (n > segtree_size) segtree_size = segtree_size << 1;
	segtree_size = segtree_size << 1;
	segtree.resize(segtree_size - 1); // one more power than the required one

	for (int64_t i = n - 1; i >= 0; i--) {
		segtree[(segtree_size >> 1) + i - 1] = arr[i];
	}

	// now build the segment tree
	// child of the ith node = 2i + 1 and 2i + 2
	// parent = (i - 1) / 2
	// Run a dfs from the root node to the leaf nodes
	init_dfs(0);

	return segtree_size >> 1;
}

bool int64_tersects(pair<int64_t, int64_t> a, pair<int64_t, int64_t> b) {
	if (a.first > b.first) swap(a, b);

	if (a.second < b.first) return 0;
	return 1;
}

int64_t query(int64_t u, int64_t q_left, int64_t q_right, int64_t node_left, int64_t node_right) {
	int64_t res = 0;
	
	if (q_left <= node_left && q_right >= node_right) {
		return segtree[u];
	}

	pair<int64_t, int64_t> q = {q_left, q_right};

	if (!int64_tersects(q, make_pair(node_left, node_right))) return 0;

	int64_t mid = (node_left + node_right) / 2;
	if (int64_tersects(q, {node_left, mid})) {
		res += query(2 * u + 1, q_left, q_right, node_left, mid);
	}
	if (int64_tersects(q, {mid + 1, node_right})) {
		res += query(2 * u + 2, q_left, q_right, mid + 1, node_right);
	}

	return res;
}

void solve() {
	int64_t n, m; cin >> n >> m;
	vector<int64_t> arr(n); for (int64_t i = 0; i < n; i++) cin >> arr[i];

	int64_t narr = init(n, arr);

	while (m--) {
		int64_t c; cin >> c;
		if (c == 1) {
			int64_t i; cin >> i;
			int64_t val; cin >> val;
			// i--;
			set_val(0, i, val, 0, narr - 1);
		} else {
			int64_t l, r; cin >> l >> r;
			r--;
			cout << query(0, l, r, 0, narr - 1) << endl;
		}
	}
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}