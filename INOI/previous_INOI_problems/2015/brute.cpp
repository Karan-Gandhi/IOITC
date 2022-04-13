#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define ll long long
#define vi std::vector<ll>
#define si set<int>
#define pb push_back

ll solve(){
    ll n;
    cin >> n ;
    ll a[n];
    ll b[n];
    ll ssum[n][n];
    ll ans = -1000000001;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        ssum[i][i]=a[i];
        ans = max(a[i], ans);
    }
    for (int i = 0; i < n; ++i){
        cin >> b[i];
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if(i==j)continue;
            ssum[i][j]=a[i]+a[j];
            if(i < j){
                for (int k = i+1; k < j; ++k){
                    ssum[i][j]+=b[k];
                }
            }
            else{
                for (int k = 0; k < j; ++k){
                    ssum[i][j]+=b[k];
                }
                for (int k = i+1; k < n; ++k)
                {
                    ssum[i][j]+=b[k];
                }
            }
            ans = max(ans, ssum[i][j]);
            cout << ans << ' ' << i << ' ' << j << ' ' << endl; 
        }
    }
    cout << ans;
    return 0;
}

int main(){
    fastio;
    ll t= 1;
    // freopen("div7.in","r",stdin); 
    // freopen("div7.out","w",stdout);
    // cin >> t;
    for (int i = 0; i < t; ++i){
        // cout << "Case #" << i+1 << ": ";
        solve();
        cout << "\n";
    }
    return 0;
}