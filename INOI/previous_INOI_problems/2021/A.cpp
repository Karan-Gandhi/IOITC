#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

vector<vector<pair<int, int>>> adj;
vector<bool> vis;
vector<int> human;
bool ok = 1;

void dfs(int u, int t1, int t2, int acc) {
	if (vis[u]) {
		if (human[u] == acc) return;
		ok = 0;
		return;
	}
	vis[u] = 1;
	human[u] = acc;

	for (auto v : adj[u]) {
		if (v.second == 1) {
			dfs(v.first, t1, t2, acc ^ t1 ^ t2); // flip the type
		} else {
			dfs(v.first, t1, t2, acc);
		}
	}
}

void solve() {
	// assume one of them to be a human then it should hold true both the ways
	// put the people who don't participate as parasites
	ok = 1;
	int n, q; cin >> n >> q;
	vis.clear();
	human.clear();
	adj.clear();
	vis.resize(n + 1);
	human.resize(n + 1);
	adj.resize(n + 1);

	fill(all(vis), 0);

	for (int i = 0; i < q; i++) {
		int type; cin >> type;
		type %= 2;
		int a, b; cin >> a >> b;
		adj[a].emplace_back(b, type);
		adj[b].emplace_back(a, type);
	}

	// int ans = 0;
	int cur = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			// this is not assigned or visited
			dfs(i, cur, cur + 1, cur);
			cur += 2;
			if (!ok) {
				cout << -1 << endl;
				return;
			}
		}
	}

	// for (int i = 1; i <= n; i++) {
	// 	cout << human[i] << ' ';
	// }
	// cout << endl;

	vector<int> cnt(cur + 2, 0);
	for (int i = 1; i <= n; i++) {
		cnt[human[i]]++;
	}

	// for (auto a : cnt) {
	// 	cout << a << ' ';
	// }
	// cout << endl;

	int ans = 0;
	for (int i = 0; i < cur; i += 2) {
		ans += max(cnt[i], cnt[i + 1]);
	}

	cout << ans << endl;

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t; cin >> t;
	while (t--)
		solve();

	return 0;
}

// for((i = 1; ; ++i)); do # if they are same then will loop forever
//     echo $i
//     ./gen.exe $i > int
//     ./ans.exe < int > out1
//     ./brut.exe < int > out2
//     diff -w out1 out2 || break
//     # diff -w <(./A < int) <(./B < int) || break
// done

// struct Seg_tree {
// 	vector<ll int> tree;
// 	ll int array_size;
// 	ll int tree_size;

// 	void init(ll int n) {
// 		array_size = n;
// 		while (__builtin_popcount(array_size) != 1) {
// 			array_size++;
// 		}
// 		tree_size = 2 * array_size - 1;
// 		tree.resize(tree_size);
// 		fill(all(tree), 0);
// 	}

// 	void pull(ll int u) {
// 		tree[u] = tree[2 * u + 1] + tree[2 * u + 2];
// 	}

// 	void update(ll int idx, ll int val) {
// 		return update_dfs(0, idx, val, 0, array_size - 1);
// 	}

// 	void update_dfs(ll int u, ll int idx, ll int val, ll int node_left, ll int node_right) {
// 		if (node_right == node_left) {
// 			assert(idx == node_left);
// 			tree[u] += val;
// 			return;
// 		}

// 		ll int mid = (node_right + node_left) / 2;

// 		if (idx <= mid) {
// 			update_dfs(2 * u + 1, idx, val, node_left, mid);
// 			pull(u);
// 		} else {
// 			update_dfs(2 * u + 2, idx, val, mid + 1, node_right);
// 			pull(u);
// 		}
// 	}

// 	ll int query(ll int l, ll int r) {
// 		// sum from x+1 to n
// 		return query_dfs(0, l, r, 0, array_size - 1);
// 	}

// 	ll int query_dfs(ll int u, ll int q_left, ll int q_right, ll int node_left, ll int node_right) {
// 		pair<ll int, ll int> q = make_pair(q_left, q_right);
// 		if (!intersects(q, make_pair(node_left, node_right))) return 0;

// 		if (q_left <= node_left && node_right <= q_right) {
// 			return tree[u];
// 		}

// 		int mid = (node_right + node_left) / 2;
// 		ll int res = 0;

// 		if (intersects(q, make_pair(node_left, mid))) {
// 			res += query_dfs(2 * u + 1, q_left, q_right, node_left, mid);
// 		} if (intersects(q, make_pair(mid + 1, node_right))) {
// 			res += query_dfs(2 * u + 2, q_left, q_right, mid + 1, node_right);
// 		}

// 		return res;
// 	}

// 	bool intersects(pair<ll int, ll int> a, pair<ll int, ll int> b) {
// 		if (a.first > b.first) swap(a, b);

// 		return a.second >= b.first;
// 	}

// 	void print() {
// 		cout << " [";
// 		for (int i = 0; i < array_size; i++) {
// 			cout << tree[array_size + i - 1] << ' ';
// 		}
// 		cout << "] " << endl;
// 	}
// };

// struct DSU {
// 	vector<int> p, s;

// 	void init(int n) {
// 		p = vector<int>(n);
// 		s = vector<int>(n + 1, 1);
// 		iota(all(p));
// 	}

// 	int get(int x) {
// 		return p[x] = (p[x] == x ? p[x] : get(p[x]));
// 	}

// 	void unite(int a, int b) {
// 		a = get(a);
// 		b = get(b);

// 		if (a == b) {
// 			return;
// 		}

// 		if (s[a] > s[b]) swap(a, b);

// 		p[a] = b;
// 		s[b] += s[a];
// 	}
// }

// #include <bits/stdc++.h>
// using namespace std;

// int rand(int a, int b) {
//     return a + rand() % (b - a + 1);
// }

// int main(int argc, char* argv[]) {
//     srand(atoi(argv[1]));

//     int n = rand(1, 20);
//     string s = "";
//     for (int i = 0; i < n; i++) {
//         if (rand(0, 1) == 1) {
//             s += '1';
//         } else {
//             s += '0';
//         }
//     }
//     assert(s.size() == n);
//     int k = rand(1, n);
//     cout << 1 << endl;
//     cout << n << ' ' << k << endl;
//     cout << s << endl;

//     return 0;
// }