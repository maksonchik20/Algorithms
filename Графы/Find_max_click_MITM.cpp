#include <bits/stdc++.h>

using namespace std;


int main() {
    int n; // кол-во вершин
    cin >> n;
    int m; // кол-во ребер
    cin >> m;
    int left_cnt = n / 2; // кол-во вершин в левой части
    int right_cnt = n - n / 2; // кол-во вершин в правой части
    vector<int> neightbor(left_cnt, 0);
    vector<int> neightbor_left(left_cnt, 0);
    vector<int> neightbor_right(right_cnt, 0);
    // вводим ребра графа
    for (int i = 0; i < m; ++i) {
        int u, v; // от [0...n-1];
        cin >> u >> v;
        if (u > v) {
            swap(u, v);
        }
        if (u < left_cnt && v >= right_cnt - (n%2)) {
            neightbor[u] += (1 << (n-v-1));
            neightbor[v] += (1 << (n-u-1));
        }
        if (u < left_cnt && v < left_cnt) {
            neightbor_left[u] += (1 << (left_cnt-v-1));
            neightbor_left[v] += (1 << (left_cnt-u-1));
        } else if (u >= right_cnt - (n % 2) && v >= right_cnt - (n % 2)) {
            neightbor_right[u-left_cnt] += (1 << (right_cnt-(v-left_cnt)-1));
            neightbor_right[v-left_cnt] += (1 << (right_cnt-(u-left_cnt)-1));
        }
    }
    for (int i = 0; i < left_cnt; ++i) {
        neightbor_left[i] += (1 << (left_cnt - i - 1));
    }
    for (int i = 0; i < right_cnt; ++i) {
        neightbor_right[i] += (1 << (right_cnt - i - 1));
    }
    int left_cnt_2 = pow(2, left_cnt);
    int right_cnt_2 = pow(2, right_cnt);
    vector<int> others(left_cnt_2);
    others[0] = right_cnt_2 - 1;
    int offset = -1;
    // считаем маску вершин правой части соединенных со всеми из маски левой
    for (int i = 1; i < left_cnt_2; ++i) {
        if ((i & (i - 1)) == 0) {
            offset++;
        }
        others[i] = (others[i - (1 << offset)] & neightbor[left_cnt-offset-1]);
    }
    // проверяем является ли маска в левой части кликой
    vector<bool> dp_left(left_cnt_2);
    dp_left[0] = 1;
    offset = -1;
    for (int i = 1; i < left_cnt_2; ++i) {
        if ((i & (i - 1)) == 0) {
            offset++;
        }
        dp_left[i] = (dp_left[i - (1 << offset)] & ((neightbor_left[left_cnt-offset-1] & i) == i));
    }
    // проверяем является ли маска в правой части кликлй
    vector<bool> dp_right(right_cnt_2);
    dp_right[0] = 1;
    offset = -1;
    for (int i = 1; i < right_cnt_2; ++i) {
        if ((i & (i - 1)) == 0) {
            offset++;
        }
        dp_right[i] = (dp_right[i - (1 << offset)] & ((neightbor_right[right_cnt-offset-1] & i) == i));
    }
    // считаем максимальную подкику в правой части
    vector<int> dp_max_subclick_right(right_cnt_2);
    dp_max_subclick_right[0] = 0;
    offset = -1;
    for (int i = 1; i < right_cnt_2; ++i) {
        if ((i & (i - 1)) == 0) {
            offset++;
        }
        dp_max_subclick_right[i] = max(dp_max_subclick_right[i - (1 << offset)], __builtin_popcount(i) * dp_right[i]);
    }
    int res = 0;
    // считаем результат
    for (int i = 0; i < left_cnt_2; ++i) {
        if (dp_left[i] == 0) {
            continue;
        }
        res = max(dp_max_subclick_right[others[i]] + __builtin_popcount(i), res);
    }
    cout << res << endl;
    return 0;
}

// ввод:
// 4
// 4
// 0 1
// 0 2
// 2 3
// 2 1
// вывод: 3

// ввод:
// 5
// 8
// 0 1
// 0 2
// 1 2
// 1 3
// 2 4
// 2 3
// 3 4
// 1 4
// вывод: 4

// ввод:
// 6
// 10
// 0 1
// 0 3
// 0 4
// 1 3
// 1 4
// 3 4
// 1 2
// 2 4
// 2 5
// 4 5
// вывод: 4
