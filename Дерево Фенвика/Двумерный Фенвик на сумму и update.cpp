#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> a;
vector<vector<int>> tree;
int n, m;

int sum(int x, int y) {
	int result = 0;
	for (int i = x; i >= 0; i = (i & (i+1)) - 1)
		for (int j = y; j >= 0; j = (j & (j+1)) - 1)
			result += tree[i][j];
	return result;
}

void add(int x, int y, int delta) {
	for (int i = x; i < n; i = (i | (i+1)))
		for (int j = y; j < m; j = (j | (j+1)))
			tree[i][j] += delta;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    ++n;
    ++m;
    a.resize(n, vector<int> (m));
    tree.resize(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; j++) {
            a[i][j] = 0;
         }
    }
    int q, x, y, x1, x2, y1, y2;
    cin >> q;
    string query;
    for (int i = 0; i < q; ++i) {
        cin >> query;
        if (query == "add") {
            cin >> x >> y;
            add(x, y, 1);
        } else {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << sum(x2, y2) - sum(x2, y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1) << endl;
        }
    }
    return 0;
}
