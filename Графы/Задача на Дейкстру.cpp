#include <bits/stdc++.h>

using namespace std;
#define ll long long


ll INF = 1000000000000000000;

bool comp_sort_second(pair<ll, ll> a, pair<ll, ll> b) {
    return a.second > b.second;
}
bool comp_sort_first(pair<ll, ll> a, pair<ll, ll> b) {
    return a.first > b.first;
}

map<pair<ll, ll>, vector<pair<pair<ll, ll>, ll>>> g;
// g[v] - vector<pair<координаты точки, вес ребра>>.
vector<pair<ll, ll>> cords;
map<pair<ll, ll>, ll> dist;

void dijkstra(pair<ll, ll> s) {
    dist[s] = 0;
    set<pair<ll, pair<ll, ll>>> q;
    q.insert({dist[s], s});
    while (!q.empty()) {
        pair<ll, ll> v = q.begin()->second;
        q.erase(q.begin());
        for (ll j = 0; j<g[v].size(); ++j) {
            pair<ll, ll> to = g[v][j].first;
            ll len = g[v][j].second;
            if (dist[v] + len < dist[to]) {
                q.erase({dist[to], to});
                dist[to] = dist[v] + len;
                q.insert({dist[to], to});
            }
        }
    }
}


int main() {
    ll n;
    cin >> n;
    ll m;
    cin >> m;
    map<pair<ll, ll>, bool> used;
    ll start_x, start_y, end_x, end_y;
    cin >> start_x >> start_y >> end_x >> end_y;
    cords.push_back({start_x, start_y});
    for (int i = 0; i < m; ++i) {
        ll x, y;
        cin >> x >> y;
        if (!used[{x, y}]) {
            used[{x, y}] = true;
            cords.push_back({x, y});
        }
    }
    sort(cords.begin(), cords.end(), comp_sort_first);
    for (int i = 0; i < cords.size() - 1; ++i) {
        ll d = min(abs(cords[i].first - cords[i + 1].first), abs(cords[i].second - cords[i + 1].second));
        dist[cords[i]] = INF;
        dist[cords[i + 1]] = INF;
        g[cords[i]].push_back({cords[i+1], d});
        g[cords[i+1]].push_back({cords[i], d});
    }
    sort(cords.begin(), cords.end(), comp_sort_second);
    for(int i = 0; i < cords.size() - 1; ++i) {
        ll d = min(abs(cords[i].first - cords[i + 1].first), abs(cords[i].second - cords[i + 1].second));
        dist[cords[i]] = INF;
        dist[cords[i + 1]] = INF;
        g[cords[i]].push_back({cords[i+1], d});
        g[cords[i+1]].push_back({cords[i], d});
    }
    pair<ll, ll> v = {start_x, start_y};
    dijkstra(v);
    ll result = INF;
    for (auto d : dist) {
        ll price = d.second;
        ll x = d.first.first;
        ll y = d.first.second;
        result = min(result, price + abs(x - end_x) + abs(y - end_y));
    }
    cout << result;
    return 0;
}
