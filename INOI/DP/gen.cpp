#include <bits/stdc++.h>
using namespace std;

int main() {
	cout << "100 100 " << (100 * 100) << endl;
	int cur = 1;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			cout << cur++ << ' ';
		}
		cout << endl;
	}

	return 0;
}