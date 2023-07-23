#include <bits/stdc++.h>

using namespace std;

struct Fenwik {
    int n;
    vector<long long> tree;

    Fenwik(int _n) {
        n = _n;
        tree.resize(n + 1);
    }
    void add(int p, int x) {
        for (; p < n; p |= p + 1) {
            tree[p] += x;
        }
    }
    long long sum(int r) {
        long long result = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            result += tree[r];
        return result;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q;
    cin >> n >> q;
    n++;
    Fenwik fw(n);
    for (int i = 0, x; i < n; i++) {
        fw.add(i, 0);
    }
    // fw.add(i, x) - присвоить i - x.
    // fw.sum(i) - взять сумму на префиксе до i
    // 1 индексация
    while (q --> 0) {
        string t;
        cin >> t;
        if (t == "rsq") {
            int l, r;
            cin >> l >> r;
            std::cout << fw.sum(r) - fw.sum(l-1) << "\n";
        } else {
            int i, x; cin >> i >> x;
            // auto curr = fw.sum(i) - fw.sum(i-1);
            // присвоить - fw.add(i - curr);
            fw.add(i, x);
        }
    }
    return 0;
}