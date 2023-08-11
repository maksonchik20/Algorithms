def minCoinsToRed(array):
    n = len(array)
    coins = 0

    i = 0
    arr = [0] * n
    while i < n:
        if array[i] == 0:
            coins += 1
            arr[i] = 1
            i += 1
        elif array[i] == 1:
            if (i >= 1):
                coins -= 1
            elif (i <= n - 2):
                arr[i + 1] = 1
            coins += 1
            arr[i] = 1
            i += 1
        elif array[i] == 2:
            coins += 1
            if (i >= 1):
                coins -= 1
            if (i <= n - 2):
                arr[i] = 1
                coins -= 1
            i += 1
            # j = i + 1
            # while j < n and array[j] != 0:
            #     array[j] -= 1
            #     j += 1
            # i = j

    return coins

# t = int(input())
# for _ in range(t):
    # n = int(input())
    # array = list(map(int, input().split()))
    # print(minCoinsToRed(array))
n = int(input())
array = list(map(int, input().split()))
result = minCoinsToRed(array)
print(result)
