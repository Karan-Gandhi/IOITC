#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define all(c) ((c).begin()), ((c).end())
#define sz(x) ((int)(x).size())

#ifdef LOCAL
#include <print.h>
#else
#define trace(...)
#define endl "\n" // remove in interactive
#endif

int add(int i, int j);

int multiply(int i, int j);

int exclusive_or(int i, int j);

int compare(int i, int j);

int put(int i);

int compose(int i);

int get_value(int i);

void solve(int n){
    if(n == 1) return;
    int inv = exclusive_or(0, 0); // 0
    vector<int> constants(n + 1);
    constants[0] = put(0);
    constants[1] = put(1);
    constants[n] = put(n);
    function<int(int)> copy_of = [&](int i){
        return exclusive_or(i, constants[0]);
    };
    function<vector<int>(vector<int>)> linearize = [&](vector<int> S){
        vector<int> ret;
        for(int i : S) ret.push_back(copy_of(i));
        ret.push_back(put(n));
        return ret;
    };

    function<vector<int>(vector<int>)> get = [&](vector<int> S){
        if((int)S.size() == 1) return S;
        vector<int> lft(S.begin(), S.begin() + S.size() / 2);
        vector<int> rgt(S.begin() + S.size() / 2, S.end());

        vector<int> A = linearize(get(lft)), B = linearize(get(rgt));

        vector<int> ret;
        
        int i = put(A[0]), j = put(B[0]), k = put(0);
        for(int iter = 0; iter < sz(A) + sz(B) - 2; iter++){
            int u = compose(i), v = compose(j); // u, v  now contain the current left, right values
            int w = compare(u, v); // left smaller

            int _w = exclusive_or(w, constants[1]); // right smaller
            inv = add(inv, multiply(w, k));
            i = add(i, w);
            j = add(j, _w);
            k = add(k, _w);
            int value = add(multiply(w, u), multiply(_w, v));
            ret.push_back(value);
        }
        return ret;
    };
    vector<int> input(n);
    iota(input.begin(), input.end(), 0);
    get(input);
    copy_of(inv);
  
}
