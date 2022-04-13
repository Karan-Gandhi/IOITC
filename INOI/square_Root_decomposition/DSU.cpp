struct DSU {
	vector<int> p, s;

	void init(int n) {
		p = vector<int>(n);
		s = vector<int>(n + 1, 1);
		iota(all(p));
	}

	int get(int x) {
		return p[x] = (p[x] == x ? p[x] : get(p[x]));
	}

	void unite(int a, int b) {
		a = get(a);
		b = get(b);

		if (a == b) {
			return;
		}

		if (s[a] > s[b]) swap(a, b);

		p[a] = b;
		s[b] += s[a];
	}
}