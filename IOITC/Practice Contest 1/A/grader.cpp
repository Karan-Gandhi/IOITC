#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;
const int BEST = 1000;
namespace{
    vector<int> values;
    string type;
    int idx;
    int asked;
}

vector<int> getLessThan(string type, int idx);

int compare(int u, int v){
    asked++;
    if(asked > MAX){
        cout << "Too many queries" << endl;
        exit(0);
    }
    if(type[u] == type[v]){
        cout << "Invalid Query: (" << u << ", " << v << ")" << endl;
        exit(0);
    }
    return values[u] < values[v] ? 0 : 1;
}

int main(){
    srand(548);
    int n; 
    cin >> n;

    assert(n >= 1 && n <= 250);

    values.resize(2 * n);
    set<int> st;

    for(int i = 0; i < 2 * n; i++){
        cin >> values[i];
        if(st.count(values[i])){
            cout << "Input Error: All values must be distinct!" << endl;
            exit(0);
        }
        st.insert(values[i]);
    }

    cin >> type >> idx;

    assert(*min_element(type.begin(), type.end()) == 'A');
    assert(*max_element(type.begin(), type.end()) == 'B');

    vector<int> perm(2 * n);
    iota(perm.begin(), perm.end(), 0);
    sort(perm.begin(), perm.end(), [&](int i, int j){return values[i] < values[j];});

    for(int i = 1; i < 2 * n; i++) if(type[perm[i]] == type[perm[i - 1]]){
        cout << "Input Error: When sorted according to values, any two adjacent indices must have different types!" << endl;        
        exit(0);
    }

    vector<int> expected;

    for(int i = 0; i < 2 * n; i++){
        if(perm[i] == idx) break;
        expected.push_back(perm[i]);
    }

    vector<int> contestant = getLessThan(type, idx);

    sort(expected.begin(), expected.end());
    sort(contestant.begin(), contestant.end());

    if(contestant != expected){
        cout << "Incorrect output!\nExpected: ";
        for(int j: expected) cout << j <<" ";
        cout << "\nGot: ";
        for(int j: contestant) cout << j <<" ";
        exit(0);
    }
    cout << "Correct!" << endl;
    cout << "Queries asked: " << asked << endl;
    cout << "Score: " << setprecision(3) << fixed << 100 * sqrt(BEST / (double)max(asked, BEST)) << endl;
}