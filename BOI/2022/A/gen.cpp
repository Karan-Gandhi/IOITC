#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int main(int argc, char* argv[]) {
	// int mx_n = 6;
	srand(atoi(argv[1]));

	int n = 6;
	// try the nth permutation of 6
	vector<int> arr(n);
	iota(arr.begin(), arr.end(), 1);
	int cnt = 0;
	do {
		if (cnt == atoi(argv[1])) {
			cout << n << endl;
			for (int i = 0; i < n; i++) cout << arr[i] << ' ';
			cout << endl;
			return;
		}
		cnt++;
	} while (next_permutation(arr.begin(), arr.end()));
}