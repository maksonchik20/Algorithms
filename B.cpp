#include <bits/stdc++.h>

using namespace std;

#define ll long long

bool comp(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first < p2.first) {
        return false;
    } else if (p1.first > p2.first) {
        return true;
    }
    return p1.second < p2.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int k;
        cin >> k;
        int arr[n];
        for (int i = 0; i < n; ++i) {
            int num;
            cin >> num;
            arr[i] = num % k;;
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (arr[i] == 0) {
                ans.push_back(i + 1);
            }
        }
        vector<pair<int, int>> vec(n);
        for (int i = 0; i < n; ++i) {
            vec[i] = {arr[i], i + 1};
        }
        sort(vec.begin(), vec.end(), comp);
        for (auto el : vec) {
            if (el.first != 0) {
                ans.push_back(el.second);
            }
        }
        for (int el : ans) {
            cout << el << " ";
        }
        cout << "\n";
     }
  return 0;
}