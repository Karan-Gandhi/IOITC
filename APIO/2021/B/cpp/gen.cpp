#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int main(int argc, char **argv) {
	srand(atoi(argv[1]));

	int n = rand(1, 20);
	int q = n * (n - 1) / 2;

	cout << n << ' ' << q << endl;

	vector<int> arr(n);
	iota(arr.begin(), arr.end(), 1);
	random_shuffle(arr.begin(), arr.end());

	for (int i : arr) cout << i << ' ';
	cout << endl;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			cout << i << ' ' << i << ' ' << j << ' ' << j << endl;
		}
	}
}