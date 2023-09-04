#include <bits/stdc++.h>

using namespace std;
vector<int> parent;
vector<int> rang;

void make_set(int v) {
	parent[v] = v;
	rang[v] = 0;
}
 
int find_set (int v) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v]);
}
 
void union_sets(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a != b) {
		if (rang[a] < rang[b])
			swap (a, b);
		parent[b] = a;
		if (rang[a] == rang[b])
			++rang[a];
	}
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    n++;
    rang.resize(n, 0);
    parent.resize(n, 0);
    map<pair<int, int>, bool> used;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        make_set(u);
        make_set(v);
        if (u > v) {
            swap(u, v);
        }
        used[{u, v}] = false;
    }
    vector<tuple<int, int, int>> queries(k);
    for (int i = k - 1; i >= 0; --i) {
        string ch;
        int u, v;
        cin >> ch >> u >> v;
        int query = 0;
        if (ch == "ask") {
            query = 1;
        }
        if (query == 0) {
            if (u > v) {
                swap(u, v);
            }
            used[{u, v}] = true;
        }
        queries[i] = {query, u, v};
    }
    for (auto el : used) {
        if (el.second == false) {
            union_sets(el.first.first, el.first.second);
        }
    }
    vector<string> result;
    for (int i = 0; i < k; ++i) {
        if (get<0>(queries[i]) == 0) {
            union_sets(get<1>(queries[i]), get<2>(queries[i]));
        } else {
            if (find_set(get<1>(queries[i])) == find_set(get<2>(queries[i]))) {
                result.push_back("YES");
            } else {
                result.push_back("NO");
            }
        }
    }
    reverse(result.begin(), result.end());
    for (auto el : result) {
        cout << el << "\n";
    }
    return 0;
}