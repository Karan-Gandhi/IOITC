#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int rand(int a, int b) {
	return rand() % (b - a + 1) + a;
}

struct DSU { // Sorry UFDS
	vector<int> p, s;
	int components;

	void init(int n) {
		p = vector<int>(n);
		iota(all(p), 0);
		s = vector<int>(n, 1);
		components = n;
	}

	int get(int x) {
		return p[x] = (p[x] == x ? x : get(p[x]));
	}

	void unite(int a, int b) {
		a = get(a);
		b = get(b);

		if (a == b) return;

		if (s[a] > s[b]) swap(a, b);

		p[a] = b;
		s[b] += s[a];
		components--;
	}

	bool same_set(int a, int b) {
		return get(a) == get(b);
	}

	int size(int x) {
		return s[get(x)];
	}
};


int main(int argc, char **argv) {
	srand(atoi(argv[1]));

	int n = rand(3, 15);
	int m = rand(n - 1, n * (n - 1) / 2);
	int q = n * (n - 1) / 2;

	// cout << n << ' ' << m << endl;

	// vect
	DSU dsu;
	dsu.init(n);
	vector<pair<int, int>> edges, final_edges;
	for (int i = 0; i < m; i++) {
		int a = rand(0, n - 1);
		dsu.unite(a, i);
		if (a != i) edges.emplace_back(a, i);
		else i--;
	}

	n = dsu.size(0);
	for (auto edge : edges) {
		if (dsu.get(edge.first) == dsu.get(0)) {
			final_edges.push_back(edge);
		}
	}
	if (n == 0) return 0;

	cout << n << ' ' << final_edges.size() << endl;

	for (auto edge : final_edges) {
		cout << edge.first << ' ' << edge.second << ' ' << rand(1, 1000) << endl;
	}

	cout << n * (n - 1) / 2 << endl;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			cout << i << ' ' << j << endl;
		}
	}
}