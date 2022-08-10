#include "pyramids.h"
#include <bits/stdc++.h>

using namespace std;

#define ll long long

vector<ll int> pref_a, pref_b;

void init(std::vector<int> a,std::vector<int> b) {
	int n = a.size();
	assert(n == int(b.size()));

	pref_a = pref_b = vector<ll int>(n + 1, 0);

	for (int i = 0; i < n; i++) {
		pref_a[i + 1] = pref_a[i] + a[i];
		pref_b[i + 1] = pref_b[i] + b[i];
	}
}

bool can_convert(int l1,int r1,int l2,int r2) {
	return (pref_a[r1 + 1] - pref_a[l1]) == (pref_b[r2 + 1] - pref_b[l2]);
}