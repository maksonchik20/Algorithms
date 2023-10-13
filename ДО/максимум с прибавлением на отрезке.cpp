#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
const ll inf = 1000000000;
 
 
vector<ll> arr;
vector<ll> tree;
vector<ll> push;
 
 
void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = arr[l];
        push[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    push[v] = 0;
}
 
void makePush(int v, int l, int r) {
    if (push[v] == 0) {
        return;
    }
    int m = (l + r) / 2;
    tree[2 * v + 1] += push[v];
    tree[2 * v + 2] += push[v];
    push[2 * v + 1] += push[v];
    push[2 * v + 2] += push[v];
    push[v] = 0;
}
 
ll get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) {
        return -inf;
    }
    if (l >= ql && r <= qr) {
        return tree[v];
    }
    makePush(v, l, r);
    int m = (l + r) / 2;
    return max(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}
 
void upd(int v, int l, int r, int ql, int qr, ll val) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (l >= ql && r <= qr) {
        push[v] += val;
        tree[v] += val;
        return;
    }
    makePush(v, l, r);
    int m = (l + r) / 2;
    upd(2 * v + 1, l, m, ql, qr, val);
    upd(2 * v + 2, m, r, ql, qr, val);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}
 
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    arr.resize(n);
    tree.resize(9 * n);
    push.resize(9 * n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    build(0, 0, n);
    // for (auto el : tree) {
    //     cout << el << " ";
    // } 
    int q;
    cin >> q;
    while (q--) {
        char ch;
        cin >> ch;
        if (ch == 'a') {
            int l, r;
            ll val;
            cin >> l >> r >> val;
            if (val) {
                upd(0, 0, n, l-1, r, val);
            }
        } else {
            int l, r;
            cin >> l >> r;
            cout << get(0, 0, n, l-1, r) << "\n";
        }
    }
    return 0;
}