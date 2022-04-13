#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v);
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

vector<vector<pair<int, pair<int, int>>>> adj;
vector<vector<pair<int, pair<int, int>>>> adj1;
int ans = 0;

void dfs1(int u, int par) {
    for (auto v : adj1[u]) {
        if (v.first == par) continue;
        adj[v.first].push_back(make_pair(u, v.second)); // parent
        dfs1(v.first, u);
    }
}

void dfs(int u, int wt) {
    bool one = 0;
    // cout << pl(u) << endl;
    // cout << pl(adj[u]) << endl;
    for (auto v : adj[u]) {
        assert(!one);
        if (v.second.first <= wt) {
            if (ans == 0) ans = v.second.second;
            ans = __gcd(ans, v.second.second);
        }
        dfs(v.first, wt);
        one = 1;
    }
    // if (!one) assert(u == 1);
}

void solve() {
    int n; cin >> n;
    int q; cin >> q;
    adj1.clear();
    adj.clear();
    adj.resize(n + 1);
    adj1.resize(n + 1);
    
    for (int i = 0; i < n - 1; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        adj1[a].push_back(make_pair(b, make_pair(c, d)));
        adj1[b].push_back(make_pair(a, make_pair(c, d)));
    }

    dfs1(1, 1);
    
    while (q--) {
        ans = 0;
        int a, b; cin >> a >> b;
        dfs(a, b);
        cout << ans << ' ';
    }
    
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    int c = 1;
    while (T--) {
        cout << "Case #" << c++ << ": ";
        solve();
    }
}