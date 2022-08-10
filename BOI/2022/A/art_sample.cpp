#include "art.h"
#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
//
// --- Sample implementation for the task art ---
//
// To compile this program with the sample grader, place:
//     art.h art_sample.cpp sample_grader.cpp
// in a single folder, then open the terminal in this directory (right-click onto an empty spot in the directory,
// left click on "Open in terminal") and enter e.g.:
//     g++ -std=c++17 art_sample.cpp sample_grader.cpp
// in this folder. This will create a file a.out in the current directory which you can execute from the terminal
// as ./a.out
// See task statement or sample_grader.cpp for the input specification
//
void solve(int n) {
    vector<int> arr(n);
    iota(all(arr), 1);

    for (int i = 0; i < n; i++) {
        int mx_j = i;
        int mx = -1;

        for (int j = i; j < n; j++) {
            // put the ith element in the end
            int temp = arr[j];
            arr.erase(arr.begin() + j);
            arr.push_back(temp);
            // swap(arr[n - 1], arr[j]);
            int res = publish(arr);
                cerr << "RES: " << res << endl;
            if (res == 0) {
                answer(arr);
                return;
            }

            if (mx == -1) {
                mx = res;
            }

            if (mx <= res) {
                mx = res;
                mx_j = j;
            }
            arr.erase(arr.begin() + n - 1);
            arr.insert(arr.begin() + j, temp);
            // swap(arr[n - 1], arr[j]);
        }
        int temp = arr[mx_j];
        arr.erase(arr.begin() + mx_j);
        arr.insert(arr.begin() + i, temp);
        // swap(arr[i], arr[mx_j]);
    }
}
