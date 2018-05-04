import sys

def build(i, l, r):
    if l + 1 == r:
        tree[i] = (l, l)
        return
    m = (l + r) // 2
    build(i * 2, l, m)
    build(i * 2 + 1, m, r)
    (q, w) = tree[i * 2]
    (e, r) = tree[i * 2 + 1]
    tree[i] = (q if A[q] < A[e] else e, w if A[w] > A[r] else r)
    (t1, t2) = tree[i]
#    print(i, t1, t2)

def get(i, l, r, a, b):
 #   print('get', i, l, r, a, b)
    if a >= r or l >= b:
        return (-1, -1)
    if l == a and r == b:
        return tree[i]
    m = (l + r) // 2
    (q, w) = get(i * 2, l, m, a, min(b, m))
    (e, t) = get(i * 2 + 1, m, r, max(a, m), b)
#    print('aft', i, l, r, a, b, q, w, e, t)
    return (q if (e == -1 or q != -1 and A[q] < A[e]) else e, w if (t == -1 or w != -1 and A[w] > A[t]) else t)

n, m = [int(x) for x in input().split()]
A = [int(x) for x in input().split()]
tree = [(-1, -1)] * (4 * n)
build(1, 0, n)
for i in range(m):
    l, r, x = [int(x) for x in input().split()]
    (pos_min, pos_max) = get(1, 0, n, l - 1, r)
    if A[pos_min] != x:
        print(pos_min + 1)
    elif A[pos_max] != x:
        print(pos_max + 1)
    else:
        print(-1)


