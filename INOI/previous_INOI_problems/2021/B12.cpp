#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

void solve() {
	int n, k; cin >> n >> k;
	string s; cin >> s;

	int last = -1;
	string ans(n, '0');

	while (1) {
		if (last == n - 1) break;
		ans[last + 1] = '1';
		int best = 0;
		int cur = 0;
		for (int i = last + 1; i < n; i++) { // optimise this part
			if (s[i] == '1') {
				cur++;
			} else {
				cur--;
			}

			if (abs(cur) <= k) {
				best = i;
			}
		}

		last = best;
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