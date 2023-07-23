#include <bits/stdc++.h>
using namespace std;



int main()
{
    int n;
    cin >> n;
    vector<stack<int>> arr(n);
    // vector<vector<int>> check_arr(n);
    // vector<int> cnt(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int k;
            cin >> k;
            // cnt[k]++;
            arr[i - 1].push(k);
            // check_arr[i - 1].push_back(k);
        }
    }
    if (n == 1) {
        return 0;
    }
    vector<pair<int, int>> res;
    if (n == 2) {
        if (!arr[0].empty()) {
            while (!arr[0].empty() && arr[0].top() == 2) {
                res.push_back({1, 2});
                arr[0].pop();
            }
        }  
        if (!arr[1].empty()) {
            while (!arr[1].empty() && arr[1].top() == 1) {
                res.push_back({2, 1});
                arr[1].pop();
            }
        }
        while (!arr[0].empty()) {
            int top = arr[0].top();
            if (top == 2) {
                cout << 0;
                return 0;
            }
            arr[0].pop();
        }
        while (!arr[1].empty()) {
            int top = arr[1].top();
            if (top == 1) {
                cout << 0;
                return 0;
            }
        }
        for (auto el : res) {
            cout << el.first << " " << el.second << "\n";
        }
        return 0;
    }
    for (int i = 2; i <= n; ++i) {
        while (!arr[i - 1].empty()) {
            cout << i << " " << 1 << endl;
            arr[0].push(arr[i - 1].top());
            arr[i - 1].pop();
        }
    }
    while (!arr[0].empty()) {
        int top = arr[0].top();
        if (top == 1 || top == 2) {
            cout << 1 << " " << 2 << endl;
            arr[1].push(top);
        } else {
            cout << 1 << " " << top << endl;
            arr[top - 1].push(top);
        }
        arr[0].pop();
    }
    int cnt = 0;
    while (!arr[1].empty()) {
        int top = arr[1].top();
        if (top == 1) {
            cout << 2 << " " << 1 << "\n";
            arr[0].push(top);
        } else {
            cout << 2 << " " << 3 << "\n";
            arr[2].push(top);
            cnt++;
        }
        arr[1].pop();
    }
    while (cnt--) {
        cout << 3 << " " << 2 << "\n";
        arr[1].push(2);
        arr[2].pop();
    }
    return 0;
}
