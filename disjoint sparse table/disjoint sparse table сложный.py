# https://codeforces.com/group/1rv4rhCsHp/contest/102954/problem/D
# Дана строка s
#  длины n
# . У каждого ее символа есть стоимость. Необходимо ответить на q
#  запросов вида «найти максимальную по стоимости подпоследовательность подстроки s
#  с l
# -й по r
# -ю позицию, равную 'mars'». Стоимость подпоследовательности определяется как сумма стоимостей ее символов.
# тест:
# ввод:
# 17
# marzamasmarrsfmar
# 4 7 2 4 1 3 10 0 5 3 7 2 4 6 1 12 99
# 3
# 2 15
# 9 13
# 1 5
# вывод:
# 24
# 19
# -1

MAXLOG = 25

class DisjointSparseTable:
    __id = []
    def __init__(self, arr, s):
        self.s = s
        sz = len(arr)
        self.maxlvl = self.clz(sz) ^ 31
        if 1 << self.maxlvl != sz:
            self.maxlvl += 1
            sz = 1 << self.maxlvl

        self.arr = arr + [self.__id for _ in range(sz - len(arr))]
        self.s = s + "z" * (sz - len(arr))
        self.st = [[{"m": -1, "ma": -1, "mar": -1, "mars": -1, "s": -1, "rs": -1, "ars": -1, "mars": -1} for _ in range(sz)] for _ in range(MAXLOG)]
        self.build(0, 0, sz)

    def build(self, lvl, l, r):
        mid = l + (r - l) // 2
        self.st[lvl][mid] = self.arr[mid]
        sl = {"s": -1, "rs": -1, "ars": -1, "mars": -1, "m": -1, "ma": -1, "mar": -1}
        rev_ind = dict(zip(list(range(l, mid)), list(range(mid - 1, l - 1, -1))))
        for i in range(mid-1, l-1, -1):
            ch = self.s[i]
            if ch == "m":
                sl["m"] = max(sl["m"], self.arr[i])
                if sl["ars"] != -1:
                    sl["mars"] = max(sl["mars"], sl["ars"] + self.arr[i])
                # if sl["ma"] != -1:
                #     sl["mar"]
            elif ch == "a":
                if sl["m"] != -1:
                    sl["ma"] = max(sl["ma"], sl["m"] + self.arr[i])
            elif ch == "r":
                if sl["ma"] != -1:
                    sl["mar"] = max(sl["mar"], sl["ma"] + self.arr[i])
            elif ch == "s":
                if sl["mar"] != -1:
                    sl["mars"] = max(sl["mars"], sl["mar"] + self.arr[i])
            self.st[lvl][i] = sl
        if True: # mid + 1 < r
            sl = {"s": -1, "rs": -1, "ars": -1, "mars": -1, "m": -1, "ma": -1, "mar": -1}
            # rev_ind = dict(zip(list(range(mid, r)), list(range(r - 1, mid - 1, -1))))
            for i in range(mid, r):
                ch = self.s[i]
                if ch == "s":
                    sl["s"] = max(self.arr[i], sl["s"])
                elif ch == "r":
                    if sl["s"] != -1:
                        sl["rs"] = max(sl["rs"], sl["s"] + self.arr[i])
                elif ch == "a":
                    if sl["rs"] != -1:
                        sl["ars"] = max(sl["ars"], sl["rs"] + self.arr[i])
                elif ch == "m":
                    if sl["ars"] != -1:
                        sl["mars"] = max(sl["mars"], sl["ars"] + self.arr[i])
                self.st[lvl][i] = sl
                # self.st[lvl][i] = self.__op(self.st[lvl][i - 1], self.arr[i])
        if l + 1 != r:
            self.build(lvl + 1, l, mid)
            self.build(lvl + 1, mid, r)

    def query(self, ql, qr):
        if ql == qr:
            return self.arr[ql]
        k = self.clz(ql ^ qr) ^ 31
        lvl = self.maxlvl - 1 - k
        ans = self.st[lvl][ql]
        print("ql", ans)
        if qr & ((1 << k) - 1):
            # ans = self.__op(ans, self.st[lvl][qr])
            print("qr", self.st[lvl][qr])
        # return ans

    @staticmethod
    def clz(x):
        for i in range(31, -1, -1):
            if x & (1 << i):
                return 31 - i

class NumArray:
    def __init__(self, nums, s):
        self.st = DisjointSparseTable(nums, s)

    def sumRange(self, left: int, right: int) -> int:
        return self.st.query(left, right)

s = input()
arr = list(map(int, input().split()))
dst = NumArray(arr, s)
q = int(input())
for _ in range(q):
    l, r = map(int, input().split())
    print(dst.sumRange(l, r))
    print(dst.st.s)