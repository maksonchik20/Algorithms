MAXLOG = 25

class DisjointSparseTable:
    def __init__(self, arr):
        sz = len(arr)
        self.maxlvl = self.clz(sz) ^ 31
        if 1 << self.maxlvl != sz:
            self.maxlvl += 1
            sz = 1 << self.maxlvl

        self.arr = arr + [self.__id for _ in range(sz - len(arr))]
        self.st = [[0 for _ in range(sz)] for _ in range(MAXLOG)]
        self.build(0, 0, sz)

    def build(self, lvl, l, r):
        mid = l + (r - l) // 2
        self.st[lvl][mid] = self.arr[mid]
        for i in range(mid - 1, l - 1, -1):
            self.st[lvl][i] = self.__op(self.st[lvl][i + 1], self.arr[i])
        if mid + 1 < r:
            self.st[lvl][mid + 1] = self.arr[mid + 1]
            for i in range(mid + 2, r):
                self.st[lvl][i] = self.__op(self.st[lvl][i - 1], self.arr[i])
        if l + 1 != r:
            self.build(lvl + 1, l, mid)
            self.build(lvl + 1, mid, r)

    def query(self, ql, qr):
        if ql == qr:
            return self.arr[ql]
        k = self.clz(ql ^ qr) ^ 31
        lvl = self.maxlvl - 1 - k
        ans = self.st[lvl][ql]
        if qr & ((1 << k) - 1):
            ans = self.__op(ans, self.st[lvl][qr])
        return ans

    @staticmethod
    def clz(x):
        for i in range(31, -1, -1):
            if x & (1 << i):
                return 31 - i

    @staticmethod
    def __op(a, b):
        return a + b

class NumArray:
    def __init__(self, nums):
        self.st = DisjointSparseTable(nums)

    def sumRange(self, left: int, right: int) -> int:
        return self.st.query(left, right)

dst = NumArray(list(map(int, input().split())))
q = int(input())
for _ in range(q):
    l, r = map(int, input().split())
    print(dst.sumRange(l, r))
