#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long 
#define pb(e) push_back(e)
#define sv(a) sort(a.begin(),a.end())
#define sa(a,n) sort(a,a+n)
#define mp(a,b) make_pair(a,b)
#define vf first
#define vs second
#define ar array
#define all(x) x.begin(),x.end()
const int inf = 0x3f3f3f3f;
const int mod = 1000000007; 
const double PI=3.14159265358979323846264338327950288419716939937510582097494459230;
bool remender(ll a , ll b){return a%b;}

//freopen("problemname.in", "r", stdin);
//freopen("problemname.out", "w", stdout);

int compare ( int u , int v);

vector <int> getLessThan (string s , int k){
	vector<int> ans;
	vector<int> mn , mx;
	int n = s.size();
	vector<int> same;
	for(int i = 0; i < n; i++){
		if(s[i] != s[k]){
			int x = compare(i , k);
			if(x == 0){
				ans.pb(i);
				mx.pb(i);
			}
			else mn.pb(i);
		}
		else if(i!=k)same.pb(i);
	}
	int a = 0 , b = 0;
	for(int i = 0; i < (int)same.size(); i++){
		int pos = same[i];
		int c = 0;
		int aa = a , bb = b;
		while(a < (int)mn.size() || b < (int)mx.size()){
			if(b >= (int)mx.size() || (c == 0 && a < (int)mn.size())){
				int x = compare(pos , mn[a]);
				if(x == 1){
					aa = a;
					break;
				}
				a++;
				c = 1;
			}
			else {
				int x = compare(pos , mx[b]);
				if(x == 0){
					ans.pb(pos);
					bb = b;
					break;
				}
				b++;
				c = 0;
			}
		}
		a = aa;
		b = bb;
	}
	return ans;
}

// #include <bits/stdc++.h>
// using namespace std;

// #define ll long long
// #define all(v) v.begin(), v.end()
// #define endl '\n'
// #define pl(var) " [" << #var << ": " << (var) << "] "

// template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
// template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
// template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }


// int compare(int u, int v); // h[v] < h[u]

// // DO NOT CHANGE ANYTHING ABOVE THIS LINE
// vector<int> getLessThan(string t, int idx){
//     // your code goes here
// 	// ABABABABABABABABAB
// 	//          ^
// 	// BABABABABABABABABA
// 	//         ^

// 	// AB <- form groups of this type
// 	// AB BA
// 	// BA

// 	// B = A
// 	// B = A - 1

// 	cout << pl(t) << endl;
//     int n = t.size();
// 	vector<vector<int>> groups; // notice this will always be alternate

// 	vector<int> as, bs;

// 	for (int i = 0; i < n; i++) {
// 		if (t[i] == 'A') as.push_back(i);
// 		else bs.push_back(i);
// 	}

// 	for (int i = 0; i < n/2; i++) {
// 		if (compare(as[i], bs[i])) groups.push_back({bs[i], as[i]});
// 		else groups.push_back({as[i], bs[i]});
// 	}

// 	cout << groups.size() << endl; // works

// 	auto merge = [&](int group1, int group2) {
// 		cout << groups << endl;
// 		vector<int> new_group;

// 		int a1, a2, b1, b2;
// 		for (int i : groups[group1]) {
// 			new_group.push_back(i);
// 		}

// 		int aIdx = 0, bIdx = 0;
// 		while (t[new_group[aIdx]] != 'A') aIdx++;
// 		while (t[new_group[bIdx]] != 'B') bIdx++;
		
// 		for (int i : groups[group2]) {
// 			cout << pl(i) << endl;
// 			if (t[i] == 'A') {
// 				// compare it with BIdx
// 				while (compare(i, new_group[bIdx])) {
// 					int save = bIdx;
// 					// go to the next bIdx
// 					while (bIdx < new_group.size() && t[new_group[bIdx]] != 'B') bIdx++;
// 					if (bIdx == new_group.size()) {
// 						// bIdx = save;
// 						cout << pl(bIdx) << endl;
// 						new_group.insert(new_group.begin() + bIdx + 1, i);
// 						bIdx = save;
// 						goto next1;
// 						// break;
// 					} else {
// 					}
// 				}

// 				cout << pl(bIdx) << endl;
// 				new_group.insert(new_group.begin() + bIdx, i);
// 				next1:;
// 			} else {
// 				while (compare(i, new_group[aIdx])) {
// 					int save = aIdx;
// 					// go to the next bIdx
// 					while (aIdx < new_group.size() && t[new_group[aIdx]] != 'A') aIdx++;
// 					if (aIdx == new_group.size()) {
// 						// bIdx = save;
// 						cout << pl(aIdx) << endl;
// 						new_group.insert(new_group.begin() + aIdx + 1, i);
// 						aIdx = save;
// 						goto next2;
// 					} else {
// 					}
// 				}

// 				cout << pl(aIdx) << endl;
// 				new_group.insert(new_group.begin() + aIdx, i);
// 				next2:;
// 			}
// 		}
// 		cout << new_group << endl;

// 		groups.erase(groups.begin() + group1);
// 		groups.erase(groups.begin() + group1);
// 		groups.insert(groups.begin() + group1, new_group);
// 	};

// 	while (groups.size() > 1) {
// 		// merge 2 consecutive groups
// 		for (int i = 0; i < ((int)groups.size()) - 1; i += 1) {
// 			merge(i, i + 1);
// 		}
// 	}

// 	// cout << groups[0] << /endl;
// 	for (int i : groups[0]) {
// 		cout << i << ' ';
// 	}
// 	cout << endl;
// 	return vector<int>();
// }