// sum a[l...r] and a[l...r] += x.

#include <bits/stdc++.h>
#include <math.h>
using namespace std;
vector<long long> tree;
vector<long long> arr;
vector<long long> push;

void build(long long v, long long l, long long r) {
    if (l + 1 == r) {
        tree[v] = arr[l];
        push[v] = 0;
        return;
    }
    long long m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = tree[2 * v  + 1] + tree[2 * v + 2];
    push[v] = 0;
}

void makePush(int v, int l, int r) {
    if (push[v] == 0) {
        return;
    }
    int m = (l + r) / 2;
    push[2 * v + 1] += push[v];
    push[2 * v + 2] += push[v];
    tree[2 * v + 1] += (m - l) * push[v];
    tree[2 * v + 2] += (r - m) * push[v];
    push[v] = 0;
}

long long get(long long v, long long l, long long r, long long ql, long long qr) {
    if (l >= qr || r <= ql) {
        return 0;
    }
    if (l >= ql && r <= qr) {
        return tree[v];
    }
    makePush(v, l, r);
    int m = (l + r) / 2;
    return get(2 * v + 1, l, m, ql, qr) + get(2 * v + 2, m, r, ql, qr);
}

void update(long long v, long long l, long long r, long long ql, long long qr, long long val) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (l >= ql && r <= qr) {
        tree[v] += (r - l) * val;
        push[v] += val;
        return;
    }
    makePush(v, l, r);
    long long m = (l + r) / 2;
    update(2 * v + 1, l, m, ql, qr, val);
    update(2 * v + 2, m, r, ql, qr, val);
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    arr.resize(n);
    tree.resize(4 * n);
    push.resize(4 * n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    build(0, 0, n);
    long long q;
    cin >> q;
    while (q--) {
        char type;
        long long l, r;
        cin >> type;
        if (type == 'g') {
            cin >> l;
            cout << get(0, 0, n, l-1, l) << " ";
        } else {
            cin >> l >> r;
            int x;
            cin >> x;
            update(0, 0, n, l-1, r, x);
        }
    }
    return 0;
}
