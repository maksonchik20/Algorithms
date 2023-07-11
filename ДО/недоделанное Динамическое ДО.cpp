
#include <bits/stdc++.h>
using namespace std;

struct S {
    int sum_subtree;
    int tl;
    int tr;
    S* left;
    S* right;
    S(int value, int tl, int tr): sum_subtree(value), tl(tl), tr(tr) {
        left = nullptr;
        right = nullptr;
    }
};

void add(vector<S>& tree, S* now,  int x) {
    if (now->tl == now->tr) {
        now->sum_subtree = x;
        return;
    }

    int mid = (now->tl + now->tr) / 2;
    if (!now->left) {
        tree.push_back(S(0, now->tl, mid));
        now->left = &tree[tree.size() - 1];
    }
    if (!now->right) {
        tree.push_back(S(0,mid + 1, now->tr));
        now->right = &tree[tree.size() - 1];
    }
    if (x <=  mid) {
        add(tree, now->left, x);
    } else {
        add(tree, now->right, x);
    }
    now->sum_subtree = now->left->sum_subtree + now->right->sum_subtree;
}

int main() {
    vector<S> tree;
    tree.push_back(S(0, 0, 10000000000));
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int x
        std::cin >> x;
        add(tree, &tree[0], x);
    }
}