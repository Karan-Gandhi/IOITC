#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));

    int n = 103, m = 102, k = 100, t = 0;
    cout << n << ' ' << m << ' ' << 1 << ' ' << k << ' ' << t << endl;

    for (int i = 0; i < m; i++) {
        cout << i + 1 << ' ' << i + 2 << " 1" << endl;
    }

    cout << n << ' ' << int(1e9) << ' ' << 1 << endl;

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ' ';
    }
    cout << endl;
}