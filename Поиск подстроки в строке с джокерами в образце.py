for _ in range(int(input())):
    t = input()
    p = input()
    cnt = 0
    res = []
    for i in range(len(t) - len(p) + 1):
        a = t[i:len(p)+i]
        flag = True
        for j in range(len(p)):
            if p[j] != '?' and p[j] != a[j]:
                flag = False
                break
        if flag is True:
            res.append(i)
            cnt += 1
    print(cnt)
    print(*res)

