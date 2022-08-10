#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

#include "machine.h"

std::vector<int> guess_permutation(int n)
{
	vector<int> arr(n);
	iota(all(arr), 1);
	arr[n - 1] = n + 2;

	vector<int> new_arr = use_machine(arr);

	for (int x = 0; x <= 255; x++) {
		vector<int> new_new_arr(n);
		vector<int> done(n + 3, 0);
		bool ok = 1;
		for (int i = 0; i < n; i++) {
			new_new_arr[i] = new_arr[i] ^ x;
		}

		for (int i = 0; i < n; i++) {
			if (new_new_arr[i] > n + 2 || new_new_arr[i] < 1) {
				ok = 0;
				break;
			}

			done[new_new_arr[i]]++;
			if(done[new_new_arr[i]] > 1) {
				ok = 0;
				break;
			}
			if (new_new_arr[i] == n || new_new_arr[i] == n + 1) {
				ok = 0;
				break;
			}
		}

		if (ok) {
			vector<pair<int, int>> ans;

			for (int i = 0; i < n; i++) {
				ans.emplace_back(new_new_arr[i], i);
			}

			sort(all(ans));
			vector<int> _ans(n);

			for (int i = 0; i < n; i++) {
				_ans[ans[i].second] = i;
			}

			return _ans;
		}		
	}

	return vector<int>(n, 0);
}