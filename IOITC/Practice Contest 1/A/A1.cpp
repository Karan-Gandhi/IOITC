#include <bits/stdc++.h>
using namespace std;

int compare(int u, int v);

// DO NOT CHANGE ANYTHING ABOVE THIS LINE
vector<int> getLessThan(string t, int idx){
    // your code goes here
	// ABABABABABABABABAB
	//          ^
	// BABABABABABABABABA
	//         ^

	// AB <- form groups of this type
	// AB BA
	// BA

	// B = A
	// B = A - 1
    int n = t.size();
    vector<int> ans;

    vector<int> good;
    vector<int> check;
    int b = 0;

    for (int i = 0; i < n; i++) {
    	if (i == idx) continue;
    	if (t[idx] != t[i]) {
    		if (compare(idx, i)) {
    			b++;
    			ans.push_back(i);
    		} else {
    			check.push_back(i);
    		}
    	} else {
    		good.push_back(i);
    	}
    }

    random_shuffle(good.begin(), good.end());
    random_shuffle(check.begin(), check.end());

    // cout << check.size() << " " << good.size() << endl;
    for (int elt : check) {
    	int ptr = 0;

    	while (ptr < good.size()) {
    		if (good.size() == b - 1) break;
    		int elt2 = *(good.begin() + ptr);
    		if (compare(elt2, elt)) {
    			good.erase(good.begin() + ptr);
    		} else ptr++;
    	}
    }
    // cout << "HERE" << endl;

    for (int i : good) ans.push_back(i);

    return ans;
}