#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<pair<int, int>> tree;

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {a[l], l};
        return;
    }
    int m = (l + r) / 2;
    build(2*v+1, l, m);
    build(2*v+2, m, r);
    tree[v] = max(tree[2*v+1], tree[2*v+2]);
}

pair<int, int> get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || l >= qr) {
        return {0, 0};
    } else if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, l, r, k;
    cin >> n;
    a.resize(n);
    tree.resize(4*n);
    for (auto& i : a) {
        cin >> i;
    }
    build(0, 0, n);
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> l;
        cin >> r;
        pair<int, int> res = get(0, 0, n, l-1, r);
        cout << res.second + 1 << "\n";
    }
    return 0;
}
