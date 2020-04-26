class DisjointSet:
    def __init__(self):
        self._parent = {}
        self._rank = {}
    def make_set(self, x):
        if x in self._parent:
            return
        self._parent[x] = x
        self._rank[x] = 1
    def find(self, x):
        if x not in self._parent:
            return
        while self._parent[x] != x:
            x, self._parent[x] = self._parent[x], self._parent[self._parent[x]]
        return x
    def union(self, x, y):
        xroot = self.find(x)
        yroot = self.find(y)
        if xroot == yroot:
            return
        if self._rank[xroot] < self._rank[yroot]:
            xroot, yroot = yroot, xroot
        self._parent[yroot] = xroot
        if self._rank[xroot] == self._rank[yroot]:
            self._rank[xroot] += 1
    def count_disjoint(self):
        found = set()
        for k in self._parent:
            found.add(self.find(k))
        return len(found)
    def sets(self):
        sets = {}
        for k in self._parent:
            p  = self.find(k)
            if p not in sets:
                sets[p] = set()
            sets[p].add(k)
        return sets

def test():
    dj = DisjointSet()
    for x in ['a', 'b', 'c', 'd']:
        dj.make_set(x)
        assert dj.find(x) == x
    dj.union('a', 'b')
    assert dj.find('b') == 'a'
    dj.union('b', 'c')
    assert dj.find('c') == 'a'
    assert dj.find('d') == 'd'
    assert dj.count_disjoint() == 2