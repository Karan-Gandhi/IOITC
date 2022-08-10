#include <bits/stdc++.h>
using namespace std;

pair<int, int> query(vector<int> S);

// DO NOT CHANGE ANYTHING ABOVE THIS LINE

vector<pair<int, int>> getEdges(int n){
    vector<bool> done(n + 1, 0);
    vector<pair<int, int>> ans;
    int expected = -1;
    int last = -1;
    set<int> leaves;
    while ((int)ans.size() != n - 1) {
        vector<int> cur_q;

        for (int i = 1; i <= n; i++) {
            if (!done[i] && leaves.count(i) == 0) cur_q.push_back(i);
        }

        if (cur_q.size() == 1) {
            // do something
            assert(last != -1);
            ans.emplace_back(last, cur_q[0]);
            break;
        }

        auto res = query(cur_q);

        if (expected == -1) {
            expected = res.second - res.first;
            last = res.first;
            leaves.insert(last);
        } else {
            if (res.second == expected) {
                expected -= res.first;
                last = res.first;
                leaves.insert(last);
            } else {
                int par = res.second - expected;
                assert(par >= 1);
                ans.emplace_back(last, par);
                leaves.clear();
                assert(last != -1);
                done[last] = 1;
                expected = -1;
                last = -1;
            }
        }
    }

    return ans;
}