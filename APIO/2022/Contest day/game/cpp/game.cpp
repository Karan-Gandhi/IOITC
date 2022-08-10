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

int n, k;

vector<vector<int>> adj;
vector<vector<bool>> can_visit;

void init(int _n, int _k) {
	n = _n;
	k = _k;

	adj.resize(n);
	can_visit = vector<vector<bool>> (k, vector<bool>(n, 0));

	for (int i = 0; i < k; i++) {
		can_visit[i][i] = 1;
	}
}

int add_teleporter(int u, int v) {
	adj[u].push_back(v);

	for (int special_planet = 0; special_planet < k; special_planet++) {
		if (can_visit[special_planet][u]) { // now we need to update the other nodes
			queue<int> q;
			q.push(v);

			while (q.size() != 0) {
				int node = q.front();
				q.pop();

				if (node <= special_planet) {
					// we found a cycle
					return 1;
				}

				if (!can_visit[special_planet][node]) { 
					// if we can visit the node from the special planet then we have already checked the node
					can_visit[special_planet][node] = 1;

					for (int v : adj[node]) {
						q.push(v);
					}
				}
			}
		}
	}

	return 0;
}