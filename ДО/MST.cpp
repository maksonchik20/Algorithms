#include <bits/stdc++.h>

using namespace std;

struct Node {
    int l;
    int r;
    vector<long long> mst;
    vector<long long> left_pointers;
    vector<long long> right_pointers;
    Node(int _l, int _r, vector<long long> arr1, vector<long long> arr2) {
        l = _l;
        r = _r;
        int left = 0;
        int right = 0;
        mst.resize(arr1.size() + arr2.size());
        left_pointers.resize(arr1.size() + arr2.size());
        right_pointers.resize(arr1.size() + arr2.size());
        int i = 0;
        while (left < arr1.size() && right < arr2.size()) {
            if (arr1[left] > arr2[right]) {
                mst[i] = arr2[right];
                right_pointers[i] = right;
                left_pointers[i] = left;
                right++;
            } else {
                mst[i] = arr1[left];
                right_pointers[i] = right;
                left_pointers[i] = left;
                left++;
            }
            i++;
        }
        while (left < arr1.size()) {
            mst[i] = arr1[left];
            left_pointers[i] = left;
            right_pointers[i] = right;
            i++;
            left++;
        }
        while (right < arr2.size()) {
            mst[i] = arr2[right];
            left_pointers[i] = left;
            right_pointers[i] = right;
            i++;
            right++;
        }
    }
};

struct SegmentTree {
    vector<Node> tree;
    vector<long long> arr;
    void build(int v, int l, int r) {
        if (l + 1 == r) {
            tree[v] = Node(l, r, arr[v], {});
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        tree[v] = Node(l, r, tree[2 * v + 1].mst, tree[2 * v + 2].mst);
    }
    int get(int v, int ql, int qr) {
        if (r <= ql || l >= qr) {
            return -1;
        }
        if (ql <= l && r <= qr) {
            return tree[v].mst
        }
    }
};



int main()
{
    int n;
    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    return 0;
}
