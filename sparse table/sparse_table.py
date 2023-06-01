n = int(input())
lst = list(map(int, input().split()))
log = [0] * (n+1)
log[1] = 0
for i in range(2, n + 1):
    log[i] = log[i//2] + 1

sparse = [[0] * n for i in range(n)]
for i in range(n):
    sparse[i][0] = lst[i]

for i in range(n-1, -1, -1):
    for j in range(log[n-i] + 1):
        sparse[i][j] = min(sparse[i][j-1], sparse[i+2**(j-1)][j-1])

r = 1
l = 4
pow = log[r-l + 1]
print(min(sparse[l])[pow], sparse[r - 2**pow + 1])
