#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main() {
    string s;
    cin >> s;
    vector<vector<int>> dp(s.length() + 1, vector<int>(85, 0));
    dp[0][0] = 1;
    for (int i = 1; i < s.length() + 1; ++i) {
        for (int balance = 0; balance < 83; ++balance) {
            if (s[i-1] == ')' || s[i-1] == '?') {
                if (balance - 1 >= 0) {
                    dp[i][balance - 1] += dp[i-1][balance];
                }
            }
            if (s[i-1] == '(' || s[i-1] == '?') {
                dp[i][balance + 1] += dp[i - 1][balance];
            }
        }
    }
    // for (int i = 0; i < s.length(); ++i) {
    //     for (int balance = 0; balance < 10; ++balance) {
    //         cout << dp[i][balance] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << s << endl;
    cout << dp[s.length()][0] << endl;
    return 0;
}
