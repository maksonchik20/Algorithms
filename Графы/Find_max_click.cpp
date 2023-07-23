#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n; // кол-во вершин
    cin >> n;
    vector<int> neightbor(n, 0);
    int m; // кол-во ребер
    cin >> m;
    // вводит ребра графа
    for (int i = 0; i < m; ++i) {
        int u, v; // от [0...n-1];
        cin >> u >> v;
        neightbor[u] += (1 << (n-v-1));
        neightbor[v] += (1 << (n-u-1));
    }
    for (int i = 0; i < n; ++i) {
        neightbor[i] += (1 << (n - i - 1));
    }
    int n_2 = pow(2, n);
    vector<bool> dp(n_2);
    dp[0] = 1;
    int offset = -1;
    int res = 0;
    for (int i = 1; i < n_2; ++i) {
        if ((i & (i - 1)) == 0) {
            offset++;
        }
        dp[i] = (dp[i - (1 << offset)] & ((neightbor[n-offset-1] & i) == i));
        if (dp[i] == 1) {
            int cnt_one_bits = __builtin_popcount(i);
            if (cnt_one_bits > res) {
                res = cnt_one_bits;
            }
        }
    }
    cout << res;
    return 0;
}
// ввод:
// 4
// 0 1
// 0 2
// 2 3
// 2 1
// вывод: 3

// ввод:
// 5
// 8
// 0 1
// 0 2
// 1 2
// 1 3
// 2 4
// 3 4
// 1 4
// 2 3
// вывод: 4