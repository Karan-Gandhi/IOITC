#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define all(v) v.begin(), v.end()

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> arr(n); 
	for (int i = 0; i < n; i++) {
		int b, c; cin >> arr[i].second >> b >> c;
		arr[i].first = b + c;
	}

	sort(all(arr));
	reverse(all(arr)); // people who take the longest to complete the eating should go first

	ll int ans = arr[0].second + arr[0].first;
	ll int prev = arr[0].second;
	for (int i = 1; i < n; i++) {
		ans = max(ans, prev + arr[i].second + arr[i].first);
		prev += arr[i].second;
		// cout << pl(ans) << pl(prev + arr[i].second + arr[i].first) << endl;
	}

	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();

	return 0;
}