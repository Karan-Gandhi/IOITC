#include "paint.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

struct Seg_tree {
	vector<ll int> tree;
	int array_size;
	int tree_size;

	ll int def = 1e9;

	void init(int n) {
		array_size = n;
		while (__builtin_popcount(array_size) != 1) {
			array_size++;
		}
		tree_size = 2 * array_size - 1;
		tree = vector<ll int>(tree_size, def);
	}

	ll int comb(ll int a, ll int b) {
		return min(a, b);
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

int minimumInstructions(int n, int m, int k, vector<int> c, vector<int> a, vector<vector<int>> b) {
	vector<int> dp(n + 1, 1e9);
	Seg_tree tree;
	tree.init(n + 1);
	tree.update(0, 0);
	dp[0] = 0;

	vector<vector<bool>> possible(n, vector<bool>(k));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < a[i]; j++) {
			possible[i][b[i][j]] = 1;
		}
	}

	auto cost = [&](int en) -> int {
		// possible to paint en - m + 1 .. en
		en--;

		vector<int> seg;
		for (int i = en - m + 1; i <= en; i++) {
			seg.push_back(c[i]);
		}

		assert((int)seg.size() == m);

		for (int i = 0; i < m; i++) {
			seg.push_back(seg[i]);
		}

		for (int start = 0; start < (int)seg.size(); start++) {
			if (start + m - 1 >= (int)seg.size()) break;
			bool ok = 1;
			for (int i = 0; i < m; i++) {
				if (!possible[i][seg[start + i]]) {
					ok = 0;
					break;
				}
			}

			if (ok) return 1;
		}

		return 1e9;
	};

	for (int i = m; i <= n; i++) {
		dp[i] = min({
			dp[i],
			(int)tree.query(i - m, i - 1) + cost(i)
		});
		tree.update(i, dp[i]);
	}

	if (dp[n] == 1e9) return -1;
    return dp[n];
}
