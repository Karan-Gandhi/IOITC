#include "jumps.h"
 
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair <ll, ll>;
int n;
const int N = 2e5 + 5;
const int M = 20;
const int INF = 1e6;
int nums[N], L[N], R[N];
vector <int> paths[N];
bool test1;
int pos[N];
int maxi[N][M];
int nx[N][M];
int greedy[N][M];
int A, B, C, D;
// int getRight(int pos, )
int getMax(int l, int r) {
    int p = 0;
    while(l + (1<<(p+1)) - 1 <= r) p++;
    return max(maxi[l][p], maxi[r - (1<<p) + 1][p]);
}
void init(int _n, vector<int> _nums) {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    test1 = 1;
    n = _n;
    nums[0] = nums[n+1] = INF;
    for (int i = 0; i < n; i++) test1 &= (_nums[i] == i+1);
    for (int i = 1; i <= n; i++) {
        maxi[i][0] = nums[i] = _nums[i-1];
        pos[nums[i]] = i;
    }
    L[0] = R[0] = 0;
    L[n+1] = R[n+1] = n+1;
    stack <int> stk;
    stk.push(0);
    for (int i = 1; i <= n; i++) {
        while(nums[stk.top()] < nums[i]) stk.pop();
        L[i] = stk.top();
        stk.push(i);
    }
    while(!stk.empty()) stk.pop();
    stk.push(n+1);
    for (int i = n; i > 0; i--) {
        while(nums[stk.top()] < nums[i]) stk.pop();
        R[i] = stk.top();
        stk.push(i);
    }
    for (int i = 1; i <= n; i++) {
        int a = L[i], b = R[i];
        nx[i][0] = b;
        if (nums[a] == INF) swap(a, b);
        if (nums[a] == INF) greedy[i][0] = i;
        if (nums[a] < nums[b] && nums[b] != INF) a = b;
        greedy[i][0] = a;
    }
    for (int j = 1; j < M; j++)
    for (int i = 1; i <= n; i++) {
        maxi[i][j] = max(maxi[i][j-1], maxi[min(n, i+(1<<(j-1)))][j-1]);
        nx[i][j] = nx[nx[i][j-1]][j-1];
        greedy[i][j] = greedy[greedy[i][j-1]][j-1];
    }
    // for (int i = 1; i <= n; i++) 
    // for (int j = i; j <= n; j++) cout << i << ',' << j << ": " << getMax(i, j) << '\n';
}
int minimum_jumps(int _A, int _B, int _C, int _D) {
    A = 1 + _A;
    B = 1 + _B;
    C = 1 + _C;
    D = 1 + _D;
    if (B+1 == C) return (nums[B] > getMax(C, D) ? -1 : 1);
    int x = getMax(A, B);
    int y = getMax(B+1, C-1);
    int z = getMax(C, D);
    if (y > z) return -1;
    if (nums[B] > z) return -1;
    int res = 0;
    if (x < y) { // 1 2 3
        int p = pos[x];
        for (int i = M-1; i >= 0; i--) {
            if (nums[greedy[p][i]] < y) {
                res += (1<<i);
                p = greedy[p][i];
            }
        }
        if (y <= nums[greedy[p][0]] && nums[greedy[p][0]] <= z) return res + 2;
        for (int i = M-1; i >= 0; i--) {
            if (nums[nx[p][i]] <= y) {
                res += (1<<i);
                p = nx[p][i];
            }
        }
        return res+1;
    } else if (x < z) { // 2 1 3
        return 1;
    } else if (x > z) { // 3 1 2
        int l = A, r = B, p = r;
        while (l <= r) {
            int mid = (l+r)>>1;
            int tmp = getMax(mid, B);
            if (tmp > y && tmp < z) return 1;
            if (tmp > z) {
                l = mid+1;
            } else {
                p = min(p, pos[tmp]);
                r = mid-1;
            }
        }
        for (int i = M-1; i >= 0; i--) {
            if (nums[nx[p][i]] <= y) {
                res += (1<<i);
                p = nx[p][i];
            }
        }
        return res + 1;
    }
}