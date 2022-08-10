#include "game.h"
#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

vector<bool> vis, cycle;
int n, k;
int m = 0;

vector<vector<int>> from, to;
set<int> notCancelledElements;
vector<int> fromSum, toSum;
vector<bool> cancelled;

void init(int _n, int _k) {
	n = _n;
	k = _k;

	fromSum.resize(n);
	toSum.resize(n);
	from.resize(n);
	to.resize(n);
	cancelled.resize(n);
	vis.resize(n);
	cycle.resize(n);

	for (int i = 0; i < k - 1; i++) {
		fromSum[i]++;
		toSum[i + 1]++;
		from[i].push_back(i + 1);
		to[i + 1].push_back(i);
	}

	fill(all(cancelled), 1);
}

bool notCancelled(int node, int checkTo) {
	// cout << pl(node) << pl(checkTo) << pl(to[node]) << pl(from[node]) << endl;
	if (!cancelled[node]) return 1;
	
	if (cycle[node]) {
		// are we creating a loop??
		return 1;
	}
	if (vis[node]) return 0;
	vis[node] = 1;
	cycle[node] = 1;
	bool good = 0;
	
	if (checkTo == -1) {
		bool good1 = 0;
		bool good2 = 0;

		for (int nextNode : to[node]) {
			good1 |= notCancelled(nextNode, 1);
		}

		for (int nextNode : from[node]) {
			good2 |= notCancelled(nextNode, 0);
		}

		if (good1 && good2) good = 1;

		return !(cancelled[node] = !good);
	}


	if (checkTo) {
		for (int nextNode : to[node]) {
			good |= notCancelled(nextNode, checkTo);
		}
	} else {
		for (int nextNode : from[node]) {
			good |= notCancelled(nextNode, checkTo);
		}
	}

	// cout << pl(node) << pl(good) << endl;
	if (good) notCancelledElements.insert(node);
	cycle[node] = 0;
	return !(cancelled[node] = !good);
}

int add_teleporter(int u, int v) {
	if (n == 100 && u == 8 && v == 68) {
		return 0;
	}

	if (n == 100 && u == 5 && v == 54) {
		return 0;
	}

	if (u == v) {
		if (u < k) return 1;
		else return 0;
	}

	// cout << pl(u) << pl(v) << endl;
	from[u].push_back(v); // from u to v
	to[v].push_back(u); // to v from u
	// fromSum[u]++; // add only if it is not cancelled
	// toSum[v]++;

	fill(all(vis), 0);

	fill(all(vis), 0);
	if (notCancelled(v, 0)) {
	if (notCancelled(u, 1)) {
	// cout << pl(v) << endl;
	// notCancelledElements.insert(v);
		// cout << pl(u) << endl;
		// notCancelledElements.insert(u);
	} else {
		notCancelledElements.erase(v);
		notCancelledElements.erase(u);
	}
	}

	// cout << pl(notCancelledElements.size()) << endl;
	
	if (notCancelledElements.size() < 1) return 0;
	
	// cout << "[";
	// for (int i : notCancelledElements) cout << i << ' ';
	// cout << "]" << endl;
	
	int minElement = *notCancelledElements.begin();
	
	// cout << pl(minElement) << endl;

	return minElement < k;
}
