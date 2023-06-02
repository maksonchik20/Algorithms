from math import inf
n = int(input()) # кол-во вершин
m = int(input()) # кол-во ребер
g = {
    1: [(2, 100), (4, 1), (5, 2)],
    2: [(3, 2)],
    3: [(5, 200), (2, 2), (6, 5)],
    4: [(1, 1), (5, 200)],
    5: [(1, 1), (4, 200), (3, 200), (6, 200)],
    6: [(5, 200), (3, 5)]
}
# for i in range(1, n + 1):
#     g[i] = []
# for i in range(m):
#     _from, to, w = map(int, input().split())
#     g[_from].append((to, w))

def dijkstra(s):
    d = [inf] * (n + 1)
    a = [0] * (n + 1)
    d[s] = 0
    for i in range(n):
        v = -1
        for u in range(1, n + 1):
            if a[u] == 0 and (v == -1 or d[u] < d[v]):
                v = u
        a[v] = True
        for u, w in g[v]:
            print(u, v)
            d[u] = min(d[u], d[v] + w)
    return d

print(dijkstra(1))