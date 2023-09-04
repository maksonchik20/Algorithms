#include <bits/stdc++.h>

using namespace std;

#define ll long long 

struct Edge {
    ll u;
    ll v;
    ll w;
    Edge(ll _u, ll _v, ll _w) {
        u = _u;
        v = _v;
        w = _w;
    }
};
vector<ll> parent;
vector<ll> rang;

void make_set(ll v) {
    parent[v] = v;
    rang[v] = 0;
}

ll find_set(ll v) {
    if (v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}

void union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rang[a] < rang[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rang[a] == rang[b]) {
            rang[a]++;
        }
    }
}

bool comp(Edge* f, Edge* s) {
    if (f->w >= s->w) {
        return true;
    }
    return false;
}

int main() {
    ll n, m;
    cin >> n >> m;
    parent.resize(n + 1);
    rang.resize(n + 1);
    vector<Edge*> edges(m);
    for (int i = 0; i < m; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges[i] = new Edge(u, v, w);
        make_set(u);
        make_set(v);
    }
    sort(edges.begin(), edges.end(), comp);
    ll result = 1000000000;
    for (int i = 0; i < edges.size(); ++i) {
        ll u = edges[i]->u;
        ll v = edges[i]->v;
        ll w = edges[i]->w;
        if (find_set(u) != find_set(v)) {
            result = min(result, w);
            union_sets(u, v);
        }
    }
    cout << result - 1 << endl;
    return 0;
}