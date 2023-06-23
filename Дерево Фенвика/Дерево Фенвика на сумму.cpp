#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<int> tree;
int n;

int sum (int r) {
    int i = r - 1;
    int res = 0;
    while (i >= 0) {
        res += tree[i];
        i = ((i & (i + 1)) - 1);
    }
    return res;
}

void add(int i, int v) {
    int j = i;
    while (j < n) {
        tree[j] += v;
        j = j | (j + 1);
    }
}

int sum(int l, int r) {
    return sum(r) - sum(l-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    a.resize(n);
    tree.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        add(i, a[i]);
    }
    int q, l, r;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> l >> r;
        cout << sum(l, r) << endl;
    }
    return 0;
}
