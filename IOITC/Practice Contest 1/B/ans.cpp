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

// int compare(int u, int v);

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
//     int n = t.size();
//     vector<int> ans;

//     vector<int> good;
//     vector<int> check;
//     int b = 0;

//     for (int i = 0; i < n; i++) {
//     	if (i == idx) continue;
//     	if (t[idx] != t[i]) {
//     		if (compare(idx, i)) {
//     			b++;
//     			ans.push_back(i);
//     		} else {
//     			check.push_back(i);
//     		}
//     	} else {
//     		good.push_back(i);
//     	}
//     }

//     random_shuffle(good.begin(), good.end());
//     random_shuffle(check.begin(), check.end());

//     // cout << check.size() << " " << good.size() << endl;
//     for (int elt : check) {
//     	int ptr = 0;

//     	while (ptr < good.size()) {
//     		if (good.size() == b - 1) break;
//     		int elt2 = *(good.begin() + ptr);
//     		if (compare(elt2, elt)) {
//     			good.erase(good.begin() + ptr);
//     		} else ptr++;
//     	}
//     }
//     // cout << "HERE" << endl;

//     for (int i : good) ans.push_back(i);

//     return ans;
// }

// #include <bits/stdc++.h>
// using namespace std;

// #define ll long long
// #define all(v) v.begin(), v.end()
// #define endl '\n'
// #define pl(var) " [" << #var << ": " << (var) << "] "

// template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
// template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
// template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

// vector<int> pref[2], suff[2];

// void solve() {
// 	int n; cin >> n;
// 	vector<pair<int, int>> arr(n);

// 	for (int i = 0; i < n; i++) cin >> arr[i].first >> arr[i].second;

// 	pref[0] = pref[1] = suff[0] = suff[1] = vector<int>(n + 2);
// 	pref[0][0] = 1e9;
// 	suff[0][n - 1] = 1e9;

// 	for (int i = 1; i <= n; i++) {
// 		pref[0][i] = min(pref[0][i - 1], arr[i - 1].second);
// 		pref[1][i] = max(pref[1][i - 1], arr[i - 1].second);
// 	}

// 	for (int i = n - 2; i >= 0; i--) {
// 		suff[0][i] = min(suff[0][i + 1], arr[i + 1].second);
// 		suff[1][i] = max(suff[1][i + 1], arr[i + 1].second);
// 	}


// 	// while combining 2 ranges we have the following options
// 	// best in left including left
// 	// 

// 	int ans = 1e9;
// 	for (int i = 0; i < n; i++) {
		
// 		// for (int j = i; j < n; j++) {
// 		// 	if (i == 0 && j == n - 1) continue;
// 		// 	int cur = arr[j].first - arr[i].first;

// 		// 	cur += max(pref[1][i], suff[1][j]) - min(pref[0][i], suff[0][j]);
// 		// 	ans = min(ans, cur);
// 		// }
// 	}

// 	cout << ans << endl;
// }

// int main() {
// #ifdef LOCAL
//     auto clock_start = chrono::high_resolution_clock::now();
//     cout << endl;
// #endif

// 	// ios::sync_with_stdio(false);
// 	// cin.tie(nullptr);

// 	int T = 1;
// 	// cin >> T;
// 	while (T--) 
// 		solve();

// #ifdef LOCAL
//     auto clock_end = chrono::high_resolution_clock::now();
//     cout << endl;
//     chrono::duration<double> elapsed = clock_end - clock_start;
//     cout << "Execution time: " << elapsed.count() << "s" << endl;
// #endif

// 	return 0;
// }