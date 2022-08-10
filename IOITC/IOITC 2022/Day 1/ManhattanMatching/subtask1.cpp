#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pl(var) " [" << #var << ": " << (var) << "] "
#define all(v) v.begin(), v.end()
#define endl '\n'

int check (string s) {
	int ss = s.size();
	stack<int> st;
	int prev = 0;
	int ans = 0;
	for (int i = 0; i < ss; i++) {
		int cur = (s[i] == '1' ? 1 : -1);
		cur += prev;
		// cout << pl(i) << pl(s[i]) << pl(st.size()) << endl;
		if (s[i] == '1' && st.size() == 0) {
			cur = 1;
		}
		prev = 0;
		while (st.size() && cur < 1) {
			cur += st.top();
			st.pop();
		}
		if (cur < 1) prev = cur;
		else st.push(cur);
		ans = max(ans, (int)st.size());
	}

	return ans;
}

void solve() {
	int n, q; cin >> n >> q;

	vector<int> ans(n);

	for (int i = 0; i < n; i++) {
		int ss; cin >> ss;
		string s; cin >> s;
		string cur = "";
		int j;
		for (j = ss - 1; j >= 0; j--) {
			if (s[j] == '1') break;
		}
		for (; j >= 0; j--) {
			cur += s[j];
		}
		s = cur;
		cur = "";
		for (j = ss - 1; j >= 0; j--) {
			if (s[j] == '1') break;
		}
		for (; j >= 0; j--) {
			cur += s[j];
		}
		ans[i] = check(cur);
		reverse(all(cur));
		ans[i] = max(ans[i], check(cur));
	}

	while (q--) {
		int l, r; cin >> l >> r;
		l--; r--;
		assert(l == r);
		cout << ans[l] << endl;
	}
}

int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(nullptr);

	int T = 1;
	// cin >> T;

	while (T--) {
		solve();
	}
}