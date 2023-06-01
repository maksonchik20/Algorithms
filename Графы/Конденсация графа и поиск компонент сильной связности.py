V, R = map(int, input().split())
g = {}
gr = {}
for i in range(1, V + 1):
    g[i] = []
    gr[i] = []

edges = []
for _ in range(R):
    _from, to = map(int, input().split())
    edges.append((_from, to))
    g[_from].append(to)
    gr[to].append(_from)

order = []
used = {}
def psevdo_topsort(graph, start):
    used[start] = True
    for to in graph[start]:
        if used.get(to) is None:
            psevdo_topsort(graph, to)
    order.append(start)
for i in range(1, V + 1):
    if used.get(i) is None:
        psevdo_topsort(g, i)
order = order[::-1]
used = {}
curComp = 1
components = {}
def dfs(graph_reversed, start):
    used[start] = True
    components[start] = curComp
    for to in graph_reversed[start]:
        if used.get(to) is None:
            dfs(graph_reversed, to)
for i in order:
    if used.get(i) is None:
        dfs(gr, i)
        curComp += 1
condensed_graph = {}
for i in range(1, curComp):
    condensed_graph[i] = []
for edge in edges:
    if components[edge[0]] != components[edge[1]]:
        condensed_graph[components[edge[0]]].append([components[edge[1]]])
print(components)
print(condensed_graph)



# 12 16
# 1 2
# 1 3
# 2 4
# 3 4
# 4 1
# 2 5
# 4 8
# 5 6
# 6 7
# 7 8
# 8 6
# 5 9
# 9 11
# 11 10
# 10 9
# 11 12