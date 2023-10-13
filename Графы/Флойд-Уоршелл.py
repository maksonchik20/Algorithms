# Флойд-Уоршелл - на основе dp. Работает за O(n^3).
# A[i][j] - наикратчайший путь из i в j 

from math import inf
n, m = map(int, input().split())
W = [[inf] * n for _ in range(n)]
for _ in range(m):
    _from, to, w = map(int, input().split())
    W[_from][to] = w
    # W[to][_from] = w
A = [[W[i][j] for j in range(n)] for i in range(n)] 
Prev = [[None for j in range(n)] for i in range(n)] 
for k in range(n):
    for i in range(n):
        for j in range(n):
            if A[i][k] < inf and A[k][j] < inf and A[i][k] + A[k][j] < A[i][j]:
                A[i][j] = A[i][k] + A[k][j]
                Prev[i][j] = Prev[k][j]
print(A)
print(Prev)
Path = []
i = 0
j = 3
while j is not None: 
    Path.append(j) 
    j = Prev[i][j] 
Path = Path[::-1]
print(Path)