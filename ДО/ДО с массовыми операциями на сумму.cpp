// #include <bits/stdc++.h>
// using namespace std;

// vector<int> a;
// vector<int> tree;
// vector<int> push;

// void build(int v, int l, int r) {
//     if (l + 1 == r) {
//         tree[v] = a[l];
//         push[v] = -1;
//         return;
//     }
//     int m = (l + r) / 2;
//     build(2*v+1, l, m);
//     build(2*v+2, m, r);
//     tree[v] = tree[2*v+1] + tree[2*v+2];
//     push[v] = -1;
// }

// void makePush(int v) {
//     if (push[v] == -1) {
//         return;
//     }
//     push[2 * v + 1] = push[v];
//     push[2 * v + 2] = push[v];
//     tree[2 * v + 1] = push[v];
//     tree[2 * v + 1] = push[v];
//     push[v] = -1;
// }

// int get(int v, int l, int r, int ql, int qr) {
//     if (r <= ql || l >= qr) {
//         return 0;
//     } 
//     if (ql <= l && r <= qr) {
//         return tree[v];
//     }
//     int m = (l + r) / 2;
//     makePush(v);
//     return get(2 * v + 1, l, m, ql, qr) + get(2 * v + 2, m, r, ql, qr);
// }

// void update(int v, int l, int r, int ql, int qr, int val) {
//     if (l >= qr || r <= ql) {
//         return;
//     }
//     if (ql <= l && r <= qr) {
//         push[v] = val;
//         tree[v] = val;
//         return;
//     }
//     makePush(v);
//     int m = (l + r) / 2;
//     update(2 * v + 1, l, m, ql, qr, val);
//     update(2 * v + 2, m, r, ql, qr, val);
//     tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
// }


// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
//     int n;
//     cin >> n;
//     a.resize(n);
//     tree.resize(4*n);
//     push.resize(4*n);
//     for (auto & i : a) {
//         cin >> i;
//     }
//     build(0, 0, n);
//     int m;
//     cin >> m;
//     char ch;
//     int left, right, val, ind;
//     for (int i = 0; i < m; ++i) {
//         cin >> ch;
//         if (ch == 'g') {
//             cin >> ind;
//             cout << get(0, 0, n, ind-1, ind) << " ";
//         } else {
//             cin >> left >> right >> val;
//             update(0, 0, n, left-1, right, val);
//         }
//     }
//     return 0;
// }


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