def sol():
    n = int(input())
    maxmax = 0
    for i in range(n):
        result = list(range(1, i+1)) + list(range(n, i, -1))
        # print(result)
        _max = 0
        _sum = 0
        for j in range(1, len(result) + 1):
            _max = max(_max, j * result[j-1])
            _sum += j * result[j-1]
        maxmax = max(maxmax, _sum - _max)
    print(maxmax)
t = int(input())
for i in range(t):
    sol()