#include <bits/stdc++.h>

using namespace std;
int INF = 1000000000;
#define ll long long

vector<int> a;
vector<int> tree;
vector<int> push;

void build(int v, int l, int r) {
     if (l + 1 == r) {
         tree[v] = a[l];
         push[v] = -1;
         return;
     }
     int m = (l + r) / 2;
     build(2*v+1, l, m);
     build(2*v+2, m, r);
     tree[v] = tree[2*v+1] + tree[2*v+2];
     push[v] = -1;
}

void makePush(int v, int l, int r, int m) {
     if (push[v] == -1) {
         return;
     }
     push[2 * v + 1] = push[v];
     push[2 * v + 2] = push[v];
     tree[2 * v + 1] = (m - l) * push[v];
     tree[2 * v + 2] = (r - m) * push[v];
     push[v] = -1;
}

int get(int v, int l, int r, int ql, int qr) {
     if (r <= ql || l >= qr) {
         return 0;
     }
     if (ql <= l && r <= qr) {
         return tree[v];
     }
     int m = (l + r) / 2;
     makePush(v, l, r, m);
     return get(2 * v + 1, l, m, ql, qr) + get(2 * v + 2, m, r, ql, qr);
}

void update(int v, int l, int r, int ql, int qr, int val) {
    if (l >= qr || r <= ql) {
         return;
     }
     if (ql <= l && r <= qr) {
         push[v] = val;
         tree[v] = (r - l) * val;
         return;
     }
     int m = (l + r) / 2;
     makePush(v, l, r, m);
     update(2 * v + 1, l, m, ql, qr, val);
     update(2 * v + 2, m, r, ql, qr, val);
     tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

unordered_map<int, int> compress(vector<ll>& a) {
    vector<ll> b = a;

    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    unordered_map<int, int> comp;
    int now = 1;
    for (auto el : b) {
        comp[el] = now;
        now++;
    }
    return comp;
}

void sol() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> black(n);
    vector<pair<ll, ll>> red(n);
    vector<ll> cords;
    map<pair<ll, ll>, pair<ll, ll>> get_red_from_black;
    map<pair<ll, ll>, pair<ll, ll>> get_black_from_red;
    for (int i = 0; i < n; ++i) {
        ll l, r, a, b;
        cin >> l >> r >> a >> b;
        black[i] = {l, r};
        red[i] = {a, b};
        get_red_from_black[black[i]] = red[i];
        get_black_from_red[red[i]] = black[i];
        cords.push_back(l);
        cords.push_back(r);
        cords.push_back(a);
        cords.push_back(b);
        cords.push_back(l+1);
        cords.push_back(r+1);
        cords.push_back(a+1);
        cords.push_back(b+1);
    }
    sort(black.begin(), black.end());
    sort(red.begin(), red.end());
    unordered_map<int, int> comp = compress(cords);
    a.resize(comp.size());
    tree.resize(4*comp.size());
    push.resize(4*comp.size());
    build(0, 0, comp.size());
    int right = 0;
    cout << endl << endl;
    for (int i = 0; i < n; ++i) {
        ll left_query = red[i].first;
        ll right_query = red[i].second;
        while (black[right].first <= red[i].second && black[right].second >= red[i].first) {
            // cout << red[i].first << " " << red[i].second << " пересекает " << black[right].first << " " << black[right].second << endl;
            right_query = max(right_query, get_red_from_black[black[right]].second);
            right++;
        }
        // comp
        cout << "от i : " << i << " запрос: " << left_query << " " << right_query << endl;;
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        sol();
    }
    return 0;
}
