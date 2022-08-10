#include <bits/stdc++.h>
using namespace std;

int add(int i, int j);

int subtract(int i, int j);

int multiply(int i, int j);

int compare(int i, int j);

int put(int i);

int compose(int i);

int n,ans;
int k0,k1,kn;

pair<int,int> order(int x,int y){
    int w = compare(x,y);
    int w_ = subtract(k1,w);
    ans = add(ans,w_);
    int val1 = add(multiply(x,w),multiply(y,w_));
    int val2 = subtract(add(x,y),val1);
    return {val1, val2};
}

vector<int> merge_sort(vector<int> indices){
    if(indices.size() <= 6){
        for(int i = 0; i < indices.size()-1; i ++){
            for(int j = 0; j < indices.size()-1-i; j ++){
                auto [i1,i2] = order(indices[j],indices[j+1]);
                indices[j] = i1;
                indices[j+1] = i2;
            }
        }
        vector<int> sorted_list;
        for(auto x:indices) sorted_list.push_back(add(x,k0));
        sorted_list.push_back(put(n+1));
        return sorted_list;
    }
    vector<int> lft, rgt;
    for(int i = 0; i < indices.size(); i ++){
        if(i < indices.size()/2) lft.push_back(indices[i]);
        else rgt.push_back(indices[i]);
    }
    lft = merge_sort(lft);
    rgt = merge_sort(rgt);
    int l = put(lft[0]),r = put(rgt[0]); // value(value(l)) = val(lft[l]) => value(l) = lft[l]
    int rptr = k0;
    vector<vector<int>> comp;
    vector<pair<int,int>> bruh;
    vector<int> sorted_list;
    for(int i = 0; i < indices.size(); i++){
        int lval = compose(l),rval = compose(r);
        int w = compare(lval,rval);
        int w_ = subtract(k1,w);
        ans = add(ans,multiply(w,rptr));
        l = add(l,w);
        r = add(r,w_);
        rptr = add(rptr,w_);
        comp.push_back({w,lval,w_,rval});
    }
    if(indices.size() != n){
        for(auto x:comp){
            bruh.push_back({multiply(x[0],x[1]),multiply(x[2],x[3])});
        }
        for(auto x:bruh) sorted_list.push_back(add(x.first,x.second));
        sorted_list.push_back(put(n+1));
    }
    return sorted_list;
}

void solve(int n){
    ::n = n;
    vector<int> v;
    for(int i = 0; i < n; i ++) v.push_back(i);
    k0 = put(0);
    k1 = put(1);
    kn = put(n);
    ans = k0;
    merge_sort(v);
    add(ans,k0);
}