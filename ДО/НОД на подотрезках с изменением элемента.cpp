#include <bits/stdc++.h>

using namespace std;

vector<int> a;
vector<int> tree;

int gcd(int a, int b) {
    return b ? gcd (b, a % b) : a;
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = gcd(tree[2 * v + 1], tree[2 * v + 2]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || l >= qr) {
        return 0;
    }
    if (ql <= l && qr >= r) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return gcd(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}

void update(int v, int l, int r, int pos, int newVal) {
    if (l + 1 == r) {
        tree[v] = newVal;
        return;
    }
    int m = (l + r) / 2;
    if (pos < m) {
        update(2 * v + 1, l, m, pos, newVal);
    } else {
        update(2 * v + 2, m, r, pos, newVal);
    }
    tree[v] = gcd(tree[2 * v + 1], tree[2 * v + 2]);
}

int main() {
    int n;
    cin >> n;
    a.resize(n);
    tree.resize(n * 4);
    for (auto& i : a) {
        cin >> i;
    }
    build(0, 0, n);
    int m;
    cin >> m;
    int l, r, ind, x;
    char ch;
    char s = 's';
    vector<int> res;
    for (int i = 0; i < m; ++i) {
        cin >> ch;
        if (ch == s) {
            cin >> l >> r;
            res.push_back(get(0, 0, n, l - 1, r));
        } else {
            cin >> ind >> x;
            update(0, 0, n, ind - 1, x);
        }
    }
    for (auto el : res) {
        cout << el << ' ';
    }
}
