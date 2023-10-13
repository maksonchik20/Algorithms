#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
const ll inf = 1000000000;
 
 
vector<ll> arr;
vector<pair<ll, ll>> tree; // min and max
vector<ll> push;

#define fi first
#define se second

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {arr[l], arr[l]};
        push[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = {min(tree[2 * v + 1].fi, tree[2 * v + 2].fi), max(tree[2 * v + 1].se, tree[2 * v + 2].se)};
    push[v] = 0;
}

void makePush(int v, int l, int r) {
    if (push[v] == 0) {
        return;
    }
    int m = (l + r) / 2;
    if (tree[2 * v + 1].fi < push[v]) {
        tree[2 * v + 1].fi = push[v];
        if (tree[2 * v + 1].se < push[v]) {
            tree[2 * v + 1].se = push[v];
        }
    }
    push[2 * v + 1] = max(push[2 * v + 1], push[v]);
    if (tree[2 * v + 2].fi < push[v]) {
        tree[2 * v + 2].fi = push[v];
        if (tree[2 * v + 2].se < push[v]) {
            tree[2 * v + 2].se = push[v];
        }
    }
    push[2 * v + 2] = max(push[2 * v + 2], push[v]);
}

pair<ll, ll> get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) {
        return {inf, -inf};
    }
    if (l >= ql && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    makePush(v, l, r);
    pair<ll, ll> lq = get(2 * v + 1, l, m, ql, qr);
    pair<ll, ll> rq = get(2 * v + 2, m, r, ql, qr);
    return {min(lq.fi, rq.fi), max(lq.se, rq.se)};
}

void upd(int v, int l, int r, int ql, int qr, ll val) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (l >= ql && r <= qr) {
        if (tree[v].fi < val) {
            tree[v].fi = val;
            if (tree[v].se < val) {
                tree[v].se = val;
            }
        }
        push[v] = max(push[v], val);
        return;
    }
    int m = (l + r) / 2;
    makePush(v, l, r);
    upd(2 * v + 1, l, m, ql, qr, val);
    upd(2 * v + 2, m, r, ql, qr, val);
    tree[v] = {min(tree[2 * v + 1].fi, tree[2 * v + 2].fi), max(tree[2 * v + 1].se, tree[2 * v + 2].se)};
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n;
    arr.resize(n);
    tree.resize(4 * n);
    push.resize(4 * n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    build(0, 0, n);
    cin >> q;
    while (q--) {
        string ch;
        cin >> ch;
        if (ch == "set") {
            int l, r;
            ll val;
            cin >> l >> r >> val;
            upd(0, 0, n, l-1, r, val);
        } else {
            int l, r;
            cin >> l >> r;
            pair<ll, ll> res = get(0, 0, n, l-1, r);
            cout << res.se - res.fi << "\n";
        }
    }
    return 0;
}