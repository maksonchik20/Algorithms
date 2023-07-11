#include <bits/stdc++.h>
using namespace std;



int main()
{
    int n;
    cin >> n;
    vector<stack<int>> arr(n);
    vector<vector<int>> check_arr(n);
    vector<int> cnt(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int k;
            cin >> k;
            cnt[k]++;
            
            arr[i - 1].push(k);
            check_arr[i - 1].push_back(k);
        }
    }
    if (n == 2) {
        for (auto el : check_arr[0]) {
            if (el != 1) {
                cout << 0;
                return 0;
            }
        }
        for (auto el : check_arr[1]) {
            if (el != 2) {
                cout << 0;
                return 0;
            }
        }
    }
    if (n == 1) {
        for (auto el : check_arr[0]) {
            if (el != 1) {
                cout << 0;
                return 0;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            while (arr[i].size() != 0) {
                
            }
        }
    }

    return 0;
}
