#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

void solve() {
	
}

int main() {
#ifdef LOCAL
    auto clock_start = chrono::high_resolution_clock::now();
    cout << endl;
#endif

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) 
		solve();

#ifdef LOCAL
    auto clock_end = chrono::high_resolution_clock::now();
    cout << endl;
    chrono::duration<double> elapsed = clock_end - clock_start;
    cout << "Execution time: " << elapsed.count() << "s" << endl;
#endif

	return 0;
}