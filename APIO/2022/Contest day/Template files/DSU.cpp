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
