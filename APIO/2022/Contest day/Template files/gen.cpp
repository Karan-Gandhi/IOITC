#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define ll long long
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

int rand(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int main(int argc, char **argv) {
	srand(atoi(argv[1]));

	return 0;
}