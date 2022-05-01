#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
	return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
	srand(atoi(argv[1]));

	int n = 10;
	int q = 1000;
	cout << n << ' ' << q << endl;
	// printf("%d\n", n);
    for(int i = 2; i <= n; ++i) {
        printf("%d %d\n", rand(1, i - 1), i);
    }

    for (int i = 0; i < n; i++) {
    	cout << rand(1, 10) << ' ';
    }
    cout << endl;

    for (int i = 0; i < q; i++) {
    	if (rand(1, 2) == 1) {
    		cout << 1 << ' ' << rand(1, n) << ' ' << rand(1, 10) << ' ' << rand(1, 10) << endl;
    	} else {
    		cout << 2 << ' ' << rand(1, n) << endl;
    	}
    }
}