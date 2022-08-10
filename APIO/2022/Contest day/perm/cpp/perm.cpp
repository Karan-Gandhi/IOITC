#include "perm.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

vector<int> ans;

int rec(ll int k) {
	ll int a = 1;
	ll int b = 0;
	ll int ind = 0;
	while (b + a <= k) {
		b += a;
		a = b + 1;
		ind++;
	}
	return ind;
}

ll int _get(int ind) {
	ll int a = 1;
	ll int b = 0;
	for (int i = 0; i < ind; i++) {
		b += a;
		a = b + 1;
	}
	return b;
}

std::vector<int> construct_permutation(long long int k)
{
	// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 90 
	k--;

	ll int lo = 0;
	vector<int> arr;
	while (k > 0) {
		int res = rec(k);
		lo -= res - 1;
		for (int i = 0; i < res; i++) {
			arr.push_back(lo++);
		}
		lo--;
		lo -= res;
		k -= _get(res);
	}

	// 89 88 ... 2 1 0
	// 89 0 88 .. 1 2
	// if (k <= 90) {
	// 	vector<int> arr(k - 1);
	// 	iota(all(arr), 0);
	// 	reverse(all(arr));
	// 	return arr;
	// } else {
		// k--;
		// vector<int> dp;
		// vector<int> arr;

		// dp.push_back(1);
		// arr.push_back(0);
		// int hi = 1;
		// int lo = -1;
		// k--;
		// while (k != 0) {
		// 	assert(k > 0);
		// 	// cout << pl(k) << endl;
		// 	int sum = 1;
		// 	for (int i = 0; i < arr.size(); i++) {
		// 		sum += dp[i];
		// 	}
		// 	// sum++;
		// 	if (k < sum) {

		// 	} else {
		// 		dp.push_back(sum);
		// 		arr.push_back(hi++);
		// 		k -= sum;
		// 	}

		// 	// cout << pl(dp) << endl << pl(sum) << endl << pl(arr) << endl;
		// }
		// // 0 1 2 3 
		map<int, int> id;
		vector<int> dup = arr;
		sort(all(dup));

		for (int i = 0; i < dup.size(); i++) id[dup[i]] = i;
		for (int i = 0; i < arr.size(); i++) arr[i] = id[arr[i]];
		// cout << pl(arr.size()) << endl;
		return arr;
	// }
	return {};
}