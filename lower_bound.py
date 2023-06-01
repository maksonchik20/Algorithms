def find(x, array, n):
    l = 0
    r = n + 1
    while l + 1 < r:
        m = (l + r) // 2
        if array[m] == x:
            l = m
            print(True)
        else:
            r = m
    # print(l)
    # return l < n and array[l] == x

print(find(7, [1,2,3,4,5,6,7,8,9,10], 9))