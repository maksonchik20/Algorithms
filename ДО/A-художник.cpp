#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> tree;
vector<int> push;
// tree[v][0] - сумма
// tree[v][1] - правая клетка на отрезке W или B
// tree[v][2] - левая клетка на отрезке W или B,
// tree[v][3] - кол-во черных отрезков
// W - 0; B - 1.

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v][0] = 0;
        tree[v][1] = 0;
        tree[v][2] = 0;
        tree[v][3] = 0;
        push[v] = -1;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    // изначально весь отрезок заполнен 0
    tree[v][0] = tree[2 * v + 1][0] + tree[2 * v + 2][0];
    tree[v][1] = 0;
    tree[v][2] = 0;
    tree[v][3] = 0;
    push[v] = -1;
}

void makePush(int v, int l, int r, int m) {
    if (push[v] == -1) {
        return;
    }
    // проталкиваем пуши
    push[2 * v + 1] = push[v];
    push[2 * v + 2] = push[v];
    // пересчитываем сумму
    tree[2 * v + 1][0] = (m - l) * push[v];
    tree[2 * v + 2][0] = (r - m) * push[v];
    // правый и левый элементы равны соответветсвенно push[v]
    tree[2 * v + 1][1] = push[v];
    tree[2 * v + 2][1] = push[v];
    tree[2 * v + 1][2] = push[v];
    tree[2 * v + 2][2] = push[v];
    // кол-во черных отрезков тоже равно push[v], либо 0, либо 1 если весь отрезок покрашен
    tree[2 * v + 1][3] = push[v];
    tree[2 * v + 2][3] = push[v];
    push[v] = -1;
}

bool leftisblack(int v, int l, int r) {
    int m = (l + r) / 2;
    makePush(v, l, r, m);

    if (l + 1 == r)
        return tree[v][0] == 1;

    return leftisblack(v * 2 + 1, l, m);
}

bool rightisblack(int v, int l, int r) {
    int m = (l + r) / 2;
    makePush(v, l, r, m);

    if (l + 1 == r)
        return tree[v][0] == 1;

    return rightisblack(v * 2 + 2, m, r);
}

void update(int v, int l, int r, int ql, int qr, int val) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        push[v] = val;
        // сумма равна количеству элементов на отрезке * изменяемое значение на отрезке
        tree[v][0] = (r - l) * val;
        // правый и левый сын равны изменяемому значению на отрезке
        tree[v][1] = val;
        tree[v][2] = val;
        // кол-во черный отрезков равно либо 1(весь отрезок покрашен в черный), либо 0. зависит от val
        tree[v][3] = val;
        return;
    }
    int m = (l + r) / 2;
    makePush(v, l, r, m);
    update(2 * v + 1, l, m, ql, qr, val);
    update(2 * v + 2, m, r, ql, qr, val);
    tree[v][0] = tree[2 * v + 1][0] + tree[2 * v + 2][0]; // пересчет суммы
    tree[v][1] = tree[2 * v + 2][1]; // правый элемент в родителе равен правому у правого сына
    tree[v][2] = tree[2 * v + 1][2]; // левый элемент в родителе равен левому у левого сына
    tree[v][3] = tree[2 * v + 1][3] + tree[2 * v + 2][3];
    // если в левом сыне правый элемент равен левому элементу в правом сыне,
    // то отрезки соединены и надо вычесть 1
    bool left = rightisblack(v * 2 + 1, l, m);
    bool right = leftisblack(v * 2 + 2, m, r);
    if (left && right) {
        tree[v][3]--;
    }

    // if (tree[2 * v + 1][1] == tree[2 * v + 2][2] && tree[2 * v + 2][2] == 1) {
    //     tree[v][3] -= 1;
    // }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n = 10000100;
    tree.resize(4*n, vector<int>(4, 0));
    push.resize(4*n);
    build(0, 0, n);
    int m;
    cin >> m;
    char type;
    int left, length;
    for (int i = 0; i < m; ++i) {
        cin >> type >> left >> length;
        if (type == 'W') {
            update(0, 0, n, 500002 + left-1, 500002 + left + length - 1, 0);
        } else {
            update(0, 0, n, 500002 + left-1, 500002 + left + length - 1, 1);
        }
        // берем ответ в корне, на всем отрезке
        cout << tree[0][3] << " " << tree[0][0] << endl;
    }
    return 0;
}
