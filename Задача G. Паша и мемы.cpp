#include <bits/stdc++.h>

using namespace std;


// Фенвик
struct Fenwik {
    int n;
    vector<long long> tree;

    Fenwik(int _n) {
        n = _n;
        tree.resize(n + 10, 0);
    }
    // add(i, x) - присвоить i - x.
    void add(int p, int x) {
        for (; p < n; p |= p + 1) {
            tree[p] += x;
        }
    }
    // fw.sum(i) - взять сумму на префиксе до i
    long long sum(int r) {
        long long result = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            result += tree[r];
        return result;
    }
};

// сжимает координаты
pair<unordered_map<int, int>, int> compress(vector<int> a) {
    vector<int> b = a;

    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    unordered_map<int, int> comp;
    int now = 1;
    for (auto el : b) {
        comp[el] = now;
        now++;
    }
    return {comp, now};
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> cord;
    vector<pair<int, int>> prev_segments(m);
    // в prev_segments хранятся все отрезки
    for (int i = 0; i < m; ++i) {
        int len;
        cin >> len;
        int _min = 1000000007;
        int _max = 0;
        for (int j = 0; j < len; ++j) {
            int num; cin >> num;
            _min = min(_min, num);
            _max = max(_max, num);
        }
        prev_segments[i] = {_min, _max};
    }
    int k;
    cin >> k;
    vector<tuple<int, int, string>> events;
    // отбираем события
    for (auto el : prev_segments) {
        if (el.second - el.first + 1 <= k) {
            events.push_back({el.second, el.first, "close"});
            events.push_back({el.first + k, el.first - 1, "check"});


            // возможно где-то лишнее добавил, но по ассимптотике все равно зайдет.
            cord.push_back(el.first);
            cord.push_back(el.first - 1);
            cord.push_back(el.second + 1);
            cord.push_back(el.second - k);
            cord.push_back(el.second);
        }
    }
    // сортируем события
    sort(events.begin(), events.end());
    pair<unordered_map<int, int>, int> cache = compress(cord);
    unordered_map<int, int> compress_cord = cache.first;
    int cnts_coords = cache.second;
    Fenwik fw(cnts_coords + 10);
    int res = 0;
    pair<int, int> res_coord;

    // считаем кол-во вложенных отрезков
    for (tuple<int, int, string> event : events) {
        if (get<2>(event) == "close") {
            fw.add(compress_cord[get<0>(event)], 1);
        } else {
            int prev_res = fw.sum(compress_cord[get<0>(event)]) - fw.sum(compress_cord[get<1>(event) + 1]);
            if (prev_res > res) {
                res = prev_res;
                res_coord = {get<0>(event) - 1, get<1>(event) + 1};
            }
        }
    }
    cout << res << endl;
    cout << res_coord.second << " " << res_coord.first << endl;
    return 0;
}