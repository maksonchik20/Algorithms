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

int sum(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x2, y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    ++n;
    // ++m;
    a.resize(n, vector<int> (m));
    tree.resize(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; j++) {
            a[i][j] = 0;
         }
    }
    long long res = 0;
    // int q, x, y, x1, x2, y1, y2;
    for (int i = 0; i < m; ++i) {
        vector<int> pos(n + 1);
        for (int j = 1; j < n; ++j) {
            int num;
            cin >> num;
            pos[num] = j;
        }
        for (int j = n - 1; j >= 1; --j) {
            // cout << pos[j] << " " << sum(0, i, pos[j] - 1, i) << endl;
            res += sum(0, i, pos[j] - 1, i);
            add(pos[j], i, 1);
            // cout << res << endl;
        }
    }
    cout << res;
    return 0;
}
