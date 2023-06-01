class UnionFind:
    def __init__(self):
        self.weights = {}
        self.parents = {}
    
    def find_dsu(self, obj):
        path = [obj]
        root = self.parents[obj]
        while root != path[-1]:
            path.append(root)
            root = self.parents[root]
        for ancestor in path:
            self.parents[ancestor] = root
        return root
    def make_set(self, obj, w=1):
        if obj not in self.parents:
            self.parents[obj] = obj
            self.weights[obj] = w
            return obj

    def union(self, *obj):
        roots = [self.find_dsu(x) for x in obj]
        heaviest = max([(self.weights[r], r) for r in roots])[1]
        for r in roots:
            if r != heaviest:
                self.weights[heaviest] += self.weights[r]
                self.parents[r] = heaviest
n = int(input())
l = list(map(int, input().split()))
dels = list(map(int, input().split()))[::-1]
dsu = UnionFind()
for i in dels:
    j = i - 1
    if dsu.parents.get(j) is None:
        dsu.make_set(j, l[j])
    if j > 0:
        if dsu.weights.get(j - 1, 0) != 0:
            dsu.union(j-1, j)
    if j < n - 1:
        if dsu.weights.get(j + 1, 0) != 0:
            dsu.union(j+1, j)
    _max = 0
    for el in dsu.weights.items():
        _max = max(_max, el[1])
    print(_max)