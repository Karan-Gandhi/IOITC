#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));

    int n = rand(1, 20);
    string s = "";
    for (int i = 0; i < n; i++) {
        if (rand(0, 1) == 1) {
            s += '1';
        } else {
            s += '0';
        }
    }
    assert(s.size() == n);
    int k = rand(1, n);
    cout << 1 << endl;
    cout << n << ' ' << k << endl;
    cout << s << endl;

    return 0;
}