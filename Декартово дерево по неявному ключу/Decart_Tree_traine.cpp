#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(238);
int INF = (int)1e9;

struct Node {
    int sz;
    int value;
    int priority;
    Node* l;
    Node* r;
    int min;
    Node(int val) {
        value = val;
        priority = rnd();
        sz = 1;
        l = r = nullptr;
        min = val;
    }
};

void makePush(Node*& t) {
    return;
};

int getSz(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->sz;
}

int getMin(Node* t) {
    if (t == nullptr) {
        return INF;
    }
    return t->min
}

void update(Node*t) {
    t->sz = 1 + getSz(t->l) + getSz(t->r);
    t->min = min({t->value, getMin(t->l), getMin(t->r)});
}

pair<Node*, Node*> split(Node* t, int x) {
    if (t == nullptr) {
        return {nullptr, nullptr};
    }
    makePush(t);
    int sz = 1 + getSz(t->l);
    if (x >= sz) {
        auto[l, r] = split(t->r, x - sz);
        t->r = l;
        update(t);
        return {t, r};
    } else {
        auto[l, r] = split(t->l, x);
        t->l = r;
        update(t);
        return (l, t);
    }
}

Node* merge(Node*l, Node*r) {
    makePush(l);
    makePush(r);
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    if (l->priority > r->priority) {
        l->r = merge(l->r, r);
        update(l);
        update(r);
        return l;
    } else {
        r->l = merge(l, r->l);
        update(l);
        update(r);
        return r;
    }
}

void print(Node*t) {
    print(t->l);
    cout << t->value << " ";
    print(t->r);
}

Node* insert(Node* t, int x) {
    Node* newNode = new Node(x);
    return merge(t, newNode);
}


int main() {
    return 0;
}