#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  std::cin >> n;
  n++;
  std::vector<std::vector<int>>table(n, std::vector<int>(log2(n)));
  for (int i = 0; i < n - 1; ++i) {
    std::cin >> table[i][0];
  }
  table[n-1][0] = (int) 1e9;
  for (int j = 1; j < log2(n); ++j) {
    for (int i = 0; i < n - (1 << j); ++i) {
      table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j-1]);
    }
  }
  int q, l, r;
  cin >> q;
  // запросы на минимум по индексам [l, r] включительно.
  while (q--) {
    cin >> l >> r;
    int t = __lg(r - l);
    if (r - l == 0) {
        cout << table[l][t] << endl;
    } else {
        cout << min(table[l][t], table[r - (1 << t) + 1][t]) << endl;
    }
}
}