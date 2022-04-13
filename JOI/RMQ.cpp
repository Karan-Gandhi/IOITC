struct RMQ {
	vector<int> arr;
	vector<vector<int>> rmq;
	int n;

	void init(vector<int> &_arr) {
		arr = _arr;
		n = _arr.size();
		// build rmq
		// for powers of 2
		int LOG = log2(n) + 2;
		rmq = vector<vector<int>> (n, vector<int>(LOG));

		for (int i = 0; i < n; i++) {
			rmq[i][0] = arr[i];
		}

		for (int i = 1; i < LOG; i++) {
			for (int j = 0; j + (1 << (i)) - 1 < n; j++) {
				rmq[j][i] = min(rmq[j][i - 1], rmq[j + (1 << (i - 1))][i - 1]);
			}
		}
	}

	int query(int l, int r) {
		int len = r - l + 1;
		int LOG = log2(len);

		return min(rmq[l][LOG], rmq[r - (1 << LOG) + 1][LOG]);
	}
};