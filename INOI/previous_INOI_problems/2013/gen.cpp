#include <bits/stdc++.h>
using namespace std;

int main() {
	cout << "300 1" << endl;

	for (int i = 0; i < 299; i++) {
		cout << 300 << ' ';
		for (int i = 0; i < 300; i++) {
			cout << int(1e9 - i) << ' ';
		}
		cout << endl;
	}
	// for (int i = 0; i < 300; i++) {
		cout << 300 << ' ';
		for (int i = 0; i < 300; i++) {
			cout << i << ' ';
		}
		cout << endl;
	// }

	return 0;
}