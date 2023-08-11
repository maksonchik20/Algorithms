#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define ll long long
#define ld long double

vector<int> tree;
vector<int> push;

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = 0;
        push[v] = -1;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = 0;
    push[v] = -1;
}
// w - 0, b - 1
void makePush(int v, int l, int r) {
    if (push[v] == -1) {
        return;
    }
    int m = (l + r) / 2;
    tree[2 * v + 1] = (m - l) * push[v];
    tree[2 * v + 2] = (r - m) * push[v];
    push[2 * v + 1] = push[v];
    push[2 * v + 2] = push[v];
    push[v] = -1;
}

int get(int v, int l, int r, int ql, int qr) {
    if (l >= ql && r <= qr) {
        return tree[v];
    }
    if (r <= ql || l >= qr) {
        return 0;
    }
    int m = (l + r) / 2;
    makePush(v, l, r);
    return get(2 * v + 1, l, m, ql, qr) + get(2 * v + 2, m, r, ql, qr);
}

void update(int v, int l, int r, int ql, int qr, int newVal) {
    if (r <= ql || l >= qr) {
        return;
    }
    if (l >= ql && r <= qr) {
        tree[v] = (r - l) * newVal;
        push[v] = newVal;
        return;
    }
    makePush(v, l, r);
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, ql, qr, newVal);
    update(2 * v + 2, m, r, ql, qr, newVal);
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

unordered_map<int, int> compress(vector<int>& cords) {
    sort(cords.begin(), cords.end());
    cords.erase(unique(cords.begin(), cords.end()), cords.end());
    unordered_map<int, int> res;
    for (int i = 0; i < cords.size(); ++i) {
        res[cords[i]] = i;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> cords;
    int min_cord = 1000000005;
    int max_cord = -1;
    int a, b;
    char c;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b >> c;
        cords.push_back(a);
        cords.push_back(b);
        min_cord = min({min_cord, a, b});
        max_cord = max({max_cord, a, b});
        if (c == 'w') {
            queries.push_back({a, b, 0});
        } else {
            queries.push_back({a, b, 1});
        }
    }
    cords.push_back(0);
    cords.push_back(1000000000);
    unordered_map<int, int> comp = compress(cords);
    tree.resize(4 * comp.size());
    push.resize(4 * comp.size());
    build(0, 0, comp.size());
    for (auto el : queries) {
        update(0, 0, comp.size(), comp[get<0>(el)], comp[get<1>(el)], comp[get<2>(el)]); 
    }
    pair<int, int> max_res = {0, 0};
    int max_len = 0;
    int left = 0;
    int right = 1;
    while (left < cords.size() && right < cords.size()) {
        while (right < cords.size() && get(0, 0, comp.size(), comp[cords[left]], comp[cords[right]]) == 0) {
            right++;
        }
        if (cords[right-1] - cords[left] > max_len) {
            max_len = cords[right-1] - cords[left];
            max_res = {cords[left], cords[right-1]};
        }
        left = right;
        right++;
    }
    // for (int i = 0; i < cords.size(); ++i) {
    //     for (int j = i + 1; j < cords.size(); ++j) {
    //         if (get(0, 0, comp.size(), comp[cords[i]], comp[cords[j]]) == 0) {
    //             if (cords[j] - cords[i] > max_len) {
    //                 max_len = cords[j] - cords[i];
    //                 max_res = {cords[i], cords[j]};
    //             }
    //         }
    //     }
    // }
    cout << max_res.first << " " << max_res.second << endl;
    return 0;
}
