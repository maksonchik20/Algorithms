#include <bits/stdc++.h>

using namespace std;
mt19937 rnd(238);

struct Node {
    int value;
    int priority;
    int sz;
    Node* l;
    Node* r;

    Node(int _value) {
        value = _value;
        priority = rnd();
        sz = 1;
        l = r = nullptr;
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

Node* insert(Node* t, int x) {
    Node* newNode = new Node(x);
    return merge(t, newNode);
}

Node* shift(Node* t, int k) {
    auto[l, r] = split(t, k);
    return merge(r, l);
}

int main() {
    Node* t = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        t = insert(t, num);
    }
    print(t);
    cout << endl;
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        t = shift(t, k);
        print(t);
        cout << endl;
    }
}