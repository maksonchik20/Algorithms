#include <bits/stdc++.h>

using namespace std;
mt19937 rnd(238);

struct Node {
    int value;
    int priority;
    int sz;
    Node* l;
    Node* r;
    int start_index;

    Node(int _value, int index) {
        value = _value;
        priority = rnd();
        sz = 1;
        l = r = nullptr;
        start_index = index;
    }
};

int getSz(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->sz;
}

void update(Node* t) {
    t->sz = getSz(t->l) + getSz(t->r) + 1;
}

pair<Node*, Node*> split(Node* t, int x) {
    if (t == nullptr) {
        return {nullptr, nullptr};
    }
    int sz = getSz(t->l) + 1;
    if (x >= sz) {
        auto[l, r] = split(t->r, x - sz);
        t->r = l;
        update(t);
        return {t, r};
    } else {
        auto[l, r] = split(t->l, x);
        t->l = r;
        update(t);
        return {l, t};
    }
}

// l < r
Node* merge(Node* l, Node* r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }

    if (l->priority > r->priority) {
        l->r = merge(l->r, r);
        update(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        update(r);
        return r;
    }
}

void print(Node* t) {
    if (t == nullptr) {
        return;
    }
    print(t->l);
    cout << t->value << ' ';
    print(t->r);
}

Node* insert(Node* t, int x, int index) {
    Node* newNode = new Node(x, index);
    return merge(t, newNode);
}

Node* delete_item(Node* t, int ind) {
    auto[left, right] = split(t, ind + 1);
    auto[left2, right2] = split(left, ind);
    return merge(left2, right);
}

int get_index(Node*& t, int ind) {
    auto[left, right] = split(t, ind + 1);
    auto[left2, right2] = split(left, ind);
    t = merge(merge(left2, right2), right);
    return right2->start_index;
}

int main() {
    Node* t = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        t = insert(t, num, i);
    }
    int q;
    cin >> q;
    while (q--) {
        int type, index;
        cin >> type >> index;
        if (type == 1) {
            t = delete_item(t, index);
        } else {
            int result = get_index(t, index);
            cout << result << endl;
        }
    }
}
