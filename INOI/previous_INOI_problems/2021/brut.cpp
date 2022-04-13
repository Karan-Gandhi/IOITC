#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;

#define INF INT_MAX
#define MOD 1000000007
#define all(x) x.begin(), x.end()

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while(T--){
        int N, K; cin >> N >> K;
        string S; cin >> S;

        int cost = 0;
        for(auto i : S) cost += (i=='1'?1:-1);
        int F = (abs(cost)+K-1)/K; F = max(F, 1);

        vi c(F);
        for(int x = 0, sum = 0; x < N; x++){
            sum += (S[x]=='1'?1:-1);
            if(sum%K) continue;

            // check if parity is the same
            if((sum>0) == (cost>0) and abs(sum/K) < F)
                c[abs(sum/K)] = x;
        }
        c[0] = -1;

        string ans(N, '0');
        for(int j = 1; j <= F; j++)
            ans[c[j-1]+1] = '1';

        cout << ans << "\n";
    }

    return 0;
}