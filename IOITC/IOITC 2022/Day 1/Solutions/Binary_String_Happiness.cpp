// --------------------------------------------------<TEMPLATE>--------------------------------------------------
// --------------------<optimizations>--------------------
/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")
*/ 
// -------------------</optimizations>--------------------
 
// ---------------<Headers and namespaces>----------------
#include <bits/stdc++.h>
using namespace std;
 
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
*/
 
// ---------------</Headers and namespaces>---------------
 
// -----------------<Defines and typedefs>----------------
// typedef tree<int,null_type,less<int>,rb_tree_tag, 
// tree_order_statistics_node_update> indexed_set; // use less_equal for multiset
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the iterator to kth largest element.(0-based)
 
typedef long double LD;
typedef long long ll;
#define int ll
#define pb push_back
#define mp make_pair
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
typedef map<int,int> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
#define F first
#define S second
#define PQ(type) priority_queue<type>
#define PQD(type) priority_queue<type,vector<type>,greater<type> >
#define WL(t) while(t --)
#define SZ(x) ((int)(x).size())
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define inrange(i,a,b) ((i>=min(a,b)) && (i<=max(a,b)))
 
/*
// -----<SCANF>-----
#define sfi(x) scanf("%d",&x);
#define sfi2(x,y) scanf("%d%d",&x,&y);
#define sfi3(x,y,z) scanf("%d%d%d",&x,&y,&z);
 
#define sfl(x) scanf("%lld",&x);
#define sfl2(x,y) scanf("%lld%lld",&x,&y);
#define sfl3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
#define sfl4(x,y,z,x1) scanf("%lld%lld%lld%lld",&x,&y,&z,&x1);
#define sfl5(x,y,z,x1,y1) scanf("%lld%lld%lld%lld%lld",&x,&y,&z,&x1,&y1);
#define sfl6(x,y,z,x1,y1,z1) scanf("%lld%lld%lld%lld%lld%lld",&x,&y,&z,&x1,&y1,&z1);
 
#define sfs(x) scanf("%s",x);
#define sfs2(x,y) scanf("%s%s",x,y);
#define sfs3(x,y,z) scanf("%s%s%s",x,y,z);
// ----</SCANF>-----
 
// ----<PRINTF>-----
#define pfi(x) printf("%d\n",x);
#define pfi2(x,y) printf("%d %d\n",x,y);
#define pfi3(x,y,z) printf("%d %d %d\n",x,y,z);
 
#define pfl(x) printf("%lld\n",x);
#define pfl2(x,y) printf("%lld %lld\n",x,y);
#define pfl3(x,y,z) printf("%lld %lld %lld\n",x,y,z);
 
#define pfs(x) printf("%s\n",x);
#define pfs2(x,y) printf("%s %s\n",x,y);
#define pfs3(x,y,z) printf("%s %s %s\n",x,y,z);
 
#define pwe(x) printf("%lld ",x); // print without end
// ----</PRINTF>----
*/
#define FLSH fflush(stdout)
#define fileIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#define PRECISION(x) cout << fixed << setprecision(x); 
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
// ----------------</Defines and typedefs>----------------
 
// -------------------<Debugging stuff>-------------------
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cout << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
 
// ------------------</Debugging stuff>-------------------
 
// ------------------------<Consts>-----------------------
const int MAXN = 1000005;
const int SQRTN = 1003;
const int LOGN = 22;
const double PI=acos(-1);
 
#ifdef int
const int INF=1e16;
#else
const int INF=1e9;
#endif
 
const int MOD = 1000000007;
const int FMOD = 998244353;
const double eps = 1e-9;
// -----------------------</Consts>-----------------------

// -------------------------<RNG>-------------------------
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count()); 
#define SHUF(v) shuffle(all(v), RNG);
// Use mt19937_64 for 64 bit random numbers.
 
// ------------------------</RNG>-------------------------
 
// ----------------------<MATH>---------------------------
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
int add(int a, int b, int c = MOD){int res=a+b;return(res>=c?res-c:res);}
int mod_neg(int a, int b, int c = MOD){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
int mul(int a, int b, int c = MOD){ll res=(ll)a*b;return(res>=c?res%c:res);}
int muln(int a, int b, int c = MOD){ll res=(ll)a*b;return ((res%c)+c)%c;}
ll mulmod(ll a,ll b, ll m = MOD){ll q = (ll)(((LD)a*(LD)b)/(LD)m);ll r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}
template<typename T>T expo(T e, T n){T x=1,p=e;while(n){if(n&1)x=x*p;p=p*p;n>>=1;}return x;}
template<typename T>T power(T e, T n, T m = MOD){T x=1,p=e;while(n){if(n&1)x=mul(x,p,m);p=mul(p,p,m);n>>=1;}return x;}
template<typename T>T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;\
t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T>T mod_inverse(T a, T n = MOD){T x,y,z=0;T d=extended_euclid(a,n,x,y);return(d>1?-1:mod_neg(x,z,n));}
 
const int FACSZ = 1; // Make sure to change this
 
int fact[FACSZ],ifact[FACSZ];
 
void precom(int c = MOD){
    fact[0] = 1;
    FOR(i,1,FACSZ) fact[i] = mul(fact[i-1],i,c);
    ifact[FACSZ-1] = mod_inverse(fact[FACSZ-1],c);
    REPD(i,FACSZ-1){
        ifact[i] = mul(i+1,ifact[i+1],c);
    }
}
 
int ncr(int n,int r,int c = MOD){
    if(r > n) return 0;
    return mul(mul(ifact[r],ifact[n-r],c),fact[n],c);
} 

// ----------------------</MATH>--------------------------
// --------------------------------------------------</TEMPLATE>--------------------------------------------------
 
void solvethetestcase();
 
signed main(){
    // comment when using scanf,printf
    FAST_IO
    int t = 1;
    // (UNCOMMENT FOR MULTIPLE TEST CASES)
    // cin >> t;
    FOR(testcase,1,t+1){
        // (UNCOMMENT FOR CODEJAM)
        // printf("Case #%lld: ",testcase); 
        solvethetestcase();
    }
}   
 
int n,q;
vi a[100005]; // total, best, prefix, suffix
int seg1[200005]; // max best
int seg2[200005]; // sum total
pair<pair<pii,pii>,pair<pii,pii>> seg3[200005]; // {{big prefix,small prefix},{big suffix, small suffix}}
 
void solvethetestcase(){
    cin >> n >> q;
    REP(i,n){
        int k; cin >> k;
        string s; cin >> s;
        int total = 0, best = 0, prefix = 0, suffix = 0;
        int cur = 0;
        for(auto c:s){
            if(c == '1'){
                cur++;
                total++;
            }
            else{
                cur--;
                total--;
                if(cur < 0) cur = 0;
            }
            remax(best, cur);
            remax(prefix, total);
        }
        reverse(all(s));
        cur = 0;
        for(auto c:s){
            if(c == '0') cur--;
            else cur++;
            remax(suffix,cur);
        }
        total = max(total,0LL);

        seg1[i+n] = best;
        seg2[i+n] = total;


        prefix -= total;
        suffix -= total;
        
        seg3[i+n] = {{{prefix,i},{0,i}},{{suffix,i},{0,i}}};
        // trace(i,prefix,suffix);
    }
    for(int i = n-1; i > 0; i --){
        seg1[i] = max(seg1[i*2],seg1[i*2+1]);
        seg2[i] = seg2[2*i]+seg2[2*i+1];
        seg3[i] = seg3[2*i];
        
        if(seg3[2*i+1].F.F > seg3[i].F.F){
            seg3[i].F.S = seg3[i].F.F;
            seg3[i].F.F = seg3[2*i+1].F.F;
            if(seg3[2*i+1].F.S > seg3[i].F.S) seg3[i].F.S = seg3[2*i+1].F.S;
        }
        else if(seg3[2*i+1].F.F > seg3[i].F.S) seg3[i].F.S = seg3[2*i+1].F.F;

        if(seg3[2*i+1].S.F > seg3[i].S.F){
            seg3[i].S.S = seg3[i].S.F;
            seg3[i].S.F = seg3[2*i+1].S.F;
            if(seg3[2*i+1].S.S > seg3[i].S.S) seg3[i].S.S = seg3[2*i+1].S.S;
        }
        else if(seg3[2*i+1].S.F > seg3[i].S.S) seg3[i].S.S = seg3[2*i+1].S.F;
    }
    WL(q){
        int l,r; cin >> l >> r;
        l --;
        l += n;
        r += n;
        int best = 0, total = 0;
        pair<pair<pii,pii>,pair<pii,pii>> bruh;
        while(l < r){
            if(l%2){
                remax(best,seg1[l]);
                total += seg2[l];
                if(seg3[l].F.F > bruh.F.F){
                    bruh.F.S = bruh.F.F;
                    bruh.F.F = seg3[l].F.F;
                    if(seg3[l].F.S > bruh.F.S) bruh.F.S = seg3[l].F.S;
                }
                else if(seg3[l].F.F > bruh.F.S) bruh.F.S = seg3[l].F.F;
                if(seg3[l].S.F > bruh.S.F){
                    bruh.S.S = bruh.S.F;
                    bruh.S.F = seg3[l].S.F;
                    if(seg3[l].S.S > bruh.S.S) bruh.S.S = seg3[l].S.S;
                }
                else if(seg3[l].S.F > bruh.S.S) bruh.S.S = seg3[l].S.F;
                l++;
            }
            if(r%2){
                --r;
                remax(best,seg1[r]);
                total += seg2[r];
                // trace(r,seg3[r].F.F.F,seg3[r].S.F.F);
                if(seg3[r].F.F > bruh.F.F){
                    bruh.F.S = bruh.F.F;
                    bruh.F.F = seg3[r].F.F;
                    if(seg3[r].F.S > bruh.F.S) bruh.F.S = seg3[r].F.S;
                }
                else if(seg3[r].F.F > bruh.F.S) bruh.F.S = seg3[r].F.F;
                if(seg3[r].S.F > bruh.S.F){
                    bruh.S.S = bruh.S.F;
                    bruh.S.F = seg3[r].S.F;
                    if(seg3[r].S.S > bruh.S.S) bruh.S.S = seg3[r].S.S;
                }
                else if(seg3[r].S.F > bruh.S.S) bruh.S.S = seg3[r].S.F;
            }
            // trace(l,r,bruh.S.F.F);
            l /= 2;
            r /= 2;
        }
        int cur = max(bruh.F.F.F+bruh.S.S.F,bruh.F.S.F+bruh.S.F.F);
        if(bruh.F.F.S != bruh.S.F.S) cur = bruh.F.F.F+bruh.S.F.F;
        cout << max(best,total+cur) << "\n";
        // trace(best,total,cur);
    }
}