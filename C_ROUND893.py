# from itertools import permutations
# from math import gcd


# n = int(input())
# lst = list(permutations(range(1, n + 1)))
# for item in lst:
#     st = set()
#     for i in range(len(item)):
#         st.add(gcd(item[i], item[(i + 1) % len(item)]))
#     if (len(st) == 3 and item[0] == 1 and item[1] == 7):
#         print(item)


# 1 2 4 3 5
# 1 2 4 5 3


t = int(input())
for _ in range(t):
    n = int(input())
    arr = [0] * (n + 1)
    result = []
    for i in range(1, n + 1):
        if (arr[i] == 0):
            arr[i] = 1
            result.append(i)
            ind = i
            while (2 * ind <= n):
                ind *= 2
                arr[ind] = 1
                result.append(ind)
    print(*result)