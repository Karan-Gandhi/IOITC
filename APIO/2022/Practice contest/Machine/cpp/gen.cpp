#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int rand(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int main(int argc, char **argv) {
	srand(atoi(argv[1]));

	// cout << 256 << endl;
	int n = rand(3, 7);
	vector<int> arr(n);
	iota(all(arr), 0);
	int res = 1;
	for (int i = 1; i <= n; i++) res *= i;

	cout << res << endl;

	do {
		cout << n << ' ' << rand(0, 225) << endl; 
		for (int i : arr) cout << i << ' ';
		cout << endl;
	} while (next_permutation(all(arr)));


	return 0;
}