#include <bits/stdc++.h>

using namespace std;

const int inf = 100000;

struct EdgeSt {
    int from;
    int to;
    int value;
    EdgeSt(int _from, int _to, int _value) {
        from=_from;
        to=_to;
        value=_value;
    }
};

int n;
vector<EdgeSt*> edge;

void dfs(int v, vector<bool>& used, vector<vector<int>>& g) {
    used[v] = 1;
    for (auto to : g[v]) {
        if (!used[to]) {
            dfs(to, used, g);
        }
    }
}

bool ford_belman(int v) {
    vector<int> dist(n, inf);
    vector<int> prev(n, -1);
    dist[v] = 0;
    bool flag;
    for (int k = 0; k < n; ++k) {
        flag = false;
        for (int i = 0; i < edge.size(); ++i) {
            if (dist[edge[i]->from] < inf) {
                if (dist[edge[i]->from] + edge[i]->value < dist[edge[i]->to]) {
                    flag = true;
                    dist[edge[i]->to] = dist[edge[i]->from] + edge[i]->value;
                    prev[edge[i]->to] = edge[i]->from;
                }
            }
        }
        if (!flag) {
            break;
        }
    }
    if (!flag) {
        return false;
    } else {
        cout << "YES" << endl;
        int start = 1;
        for (int i = 0; i < n; ++i) {
            start = prev[start];
        }
        vector<int> used(n, false);
        used[start] = true;
        vector<int> path_cycle;
        path_cycle.push_back(start + 1);
        for (int i = 0; i < n; ++i) {
            start = prev[start];
            path_cycle.push_back(start + 1);
            if (used[start]) {
                break;
            }
            used[start] = true;
        }
        cout << path_cycle.size() << endl;
        for (auto el : path_cycle) {
            cout << el << " ";
        }
        return true;
    }
}


// поиск отрицательного цикла в графе. Могут быть несколько компонент связности.
int main() {
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int d;
            cin >> d;
            if (d != inf) {
                g[j].push_back(i);
                edge.push_back(new EdgeSt(j, i, d));
            }
        }
    }
    vector<int> comp;
    vector<bool> used(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, used, g);
            comp.push_back(i);
        }
    }
    bool flag = true;
    for (auto v : comp) {
        bool res = ford_belman(v);
        if (res == true) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "NO" << endl;
    }
    return 0;
}