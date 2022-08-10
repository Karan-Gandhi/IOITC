#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll int rand(ll int a, ll int b) {
	return rand() % (b - a + 1) + a;
}

int main(int argc, char **argv) {
	srand(atoi(argv[1]));
	ll int n = rand(2, 250);
	vector<ll int> arr(2 * n);
	string s(2 * n, 'A');
	map<ll int, bool> done;
	for (ll int i = 0; i < n; i++) {
		s[i] = 'A';
		s[i + n] = 'B';
		// cout << i << endl;
		do {
			// cout << arr[i] << endl;
			arr[i] = rand(0ll, (ll int)1e9);
		} while (done[arr[i]]);
		done[arr[i]] = 1;

		do {
			arr[i + n] = rand(0, 1e9);
		} while (done[arr[i + n]]);
		done[arr[i + n]] = 1;
	}

	vector<pair<ll int, int>> dup(2 * n); for (int i = 0; i < 2 * n; i++) dup[i] = {arr[i], i};
	sort(dup.begin(), dup.end());

	for (int i = 0; i < 2 * n; i++) {
		// cout << dup[i].second << endl;
		s[dup[i].second] = ((i % 2 == 0) ? 'A' : 'B');
	}

	// for (ll int i = n; i < 2 * n; i++) {

	// }

	cout << n << endl;
	for (ll int i : arr) cout << i << ' ';
	cout << endl;
	cout << s << endl;

	return 0;
}