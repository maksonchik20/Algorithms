// https://www.codechef.com/problems/GENETICS?tab=statement
// рейтинг задачи 2301

#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(238);

struct Node {
    char value;
    long long priority;
    long long sz;
    Node* l;
    Node* r;
    long long A, G, T, C;
    Node(char _value) {
        value = _value;
        sz = 1;
        priority = rnd();
        l = r = nullptr;
        A = G = T = C = 0;
        if (_value == 'A') {
            A++;
        } else if (_value == 'G') {
            G++;
        } else if (_value == 'T') {
            T++;
        } else if (_value == 'C') {
            C++;
        }
    }
};


int getSz(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->sz;
}

long long getA(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->A;
}

long long getG(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->G;
}

long long getT(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->T;
}

long long getC(Node* t) {
    if (t == nullptr) {
        return 0;
    }
    return t->C;
}

void update(Node* t) {
    t->sz = 1 + getSz(t->l) + getSz(t->r);
    t->A = getA(t->l) + getA(t->r);
    t->G = getG(t->l) + getG(t->r);
    t->T = getT(t->l) + getT(t->r);
    t->C = getC(t->l) + getC(t->r);
    if (t->value == 'A') {
            t->A++;
    } else if (t->value == 'G') {
        t->G++;
    } else if (t->value == 'T') {
        t->T++;
    } else if (t->value == 'C') {
        t->C++;
    }
}

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
        update(r);
        return l;
    } else {
        r->l = merge(l, r->l);
        update(r);
        update(l);
        return r;
    }
}

pair<Node*, Node*> split(Node* t, long long x) {
    if (t == nullptr) {
        return {nullptr, nullptr};
    }
    
    long long sz = getSz(t->l);
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

void print(Node* t) {
    if (t == nullptr) {
        return;
    }
    print(t->l);
    cout << t->value << " ";
    print(t->r);
}

Node* insert(Node* t, char value) {
    Node* newNode = new Node(value);
    return merge(t, newNode);
}

vector<long long> getCnt(Node*& t, long long l, long long r) {
    auto[left, right] = split(t, r);
    auto[left2, right2] = split(left, l);
    vector<long long> result;
    result.push_back(getA(right2));
    result.push_back(getG(right2));
    result.push_back(getT(right2));
    result.push_back(getC(right2));
    t = merge(merge(left2, right2), right);
    return result;
}

int main() {
    Node* t = nullptr;
    int n;
    cin >> n;
    vector<Node*> DNK(n);
    // for (int i = 0; i < n)
    
	return 0;
}
