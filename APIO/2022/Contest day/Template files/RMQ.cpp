struct RMQ {
	const int LOG = 20;
	vector<int> bin_log = vector<int>((1 << LOG) + 1);
	vector<vector<ll int>> rmq;

	void init(vector<int> arr) {
		bin_log[1] = 0;
		bin_log[2] = 1;
		int n = arr.size();

		for (int i = 3; i <= (1 << LOG); i++) {
			bin_log[i] = bin_log[i / 2] + 1;
		}

		rmq = vector<vector<ll int>>(arr.size(), vector<ll int>(LOG));

		for (int i = 0; i < n; i++) {
			rmq[i][0] = arr[i];
		}

		for (int i = 1; i <= LOG; i++) {
			for (int j = 0; j + (1 << i) - 1 < n; j++) {
				rmq[j][i] = min(rmq[j][i - 1], rmq[j + (1 << (i - 1))][i - 1]);
			}
		}
	}

	ll int query(int l, int r) {
		int len = r - l + 1;
		int idx = bin_log[len];

		return min(rmq[l][idx], rmq[r - (1 << idx) + 1][idx]);
	}
};