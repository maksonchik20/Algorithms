#include <bits/stdc++.h>

using namespace std;
mt19937 rnd(238);

struct Node {
    int value;
    int priority;
    int sz;
    Node* l;
    Node* r;
    bool rev;
    int min;
    Node(int _value) {
        value = _value;
        priority = rnd();
        sz = 1;
        l = r = nullptr;
        rev = false;
        min = _value;
    }
};

void makePush(Node*& t);

int getSz(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->sz;
}


int getMin(Node* t) {
    if (t == nullptr) {
        return (int)1e9;
    }
    return t->min;
}

void update(Node* t) {
    t->sz = getSz(t->l) + getSz(t->r) + 1;
    t->min = min(t->value, min(getMin(t->l), getMin(t->r)));
}

pair<Node*, Node*> split(Node* t, int x) {
    if (t == nullptr) {
        return {nullptr, nullptr};
    }
    makePush(t);
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

Node* merge(Node* l, Node* r) {
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
        update(r);
        update(l);
        return r;
    }

}

void makePush(Node*& t){
    if (t && t->rev) {
		t->rev = false;
		swap (t->l, t->r);
		if (t->l)  t->l->rev ^= true;
		if (t->r)  t->r->rev ^= true;
	}
}

void print(Node* t) {
    if (t == nullptr) {
        return;
    }
    makePush(t);
    print(t->l);
    cout << t->value << " ";
    print(t->r);
}

Node* insert(Node* t, int x) {
    Node* newNode = new Node(x);
    return merge(t, newNode);
}

int getMin(Node*& t, int l, int r) {
    auto[left, right] = split(t, r);
    auto[left2, right2] = split(left, l);
    int mins = min(right2->value, min(getMin(right2->l), getMin(right2->r)));
    t = merge(merge(left2, right2), right);
    return mins;
}

void reverse(Node*& t, int l, int r) {
    auto[left, right] = split(t, r);
    auto[left2, right2] = split(left, l);
    right2->rev = !right2->rev;
    t = merge(merge(left2, right2), right);
}

int main() {
    Node* t = nullptr;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        t = insert(t, num);
    }
    vector<int> res;
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            reverse(t, l-1, r);
        } else {
            res.push_back(getMin(t, l-1, r));
        }
    }
    for (auto el : res) {
        cout << el << "\n";    
    }
    return 0;
}