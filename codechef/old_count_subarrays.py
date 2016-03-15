def get(i, L, R, p):
    if (L + 1 == R):
        return tree[i]
    M = (L + R) // 2
    if p < M:
        return get(i * 2, L, M, p) + tree[i]
    else:
        return get(i * 2 + 1, M, R, p) + tree[i]

def upd(i, L, R, A, B, val):
    if L >= B or A >= R:
        return
    if L == A and R == B:
        tree[i] += val
        return
    M = (L + R) // 2
    upd(i * 2, L, M, A, min(M, B), val)
    upd(i * 2 + 1, M, R, max(A, M), B, val)


test_count = int(input())
for test in range(test_count):
    n = int(input())
    a = [int(x) for x in input().split()]
    order = [(a[i], i) for i in range(n)]
    order.sort()
    print(order)
    pos = [0] * n
    for i in range(n):
        (x, y) = order[i]
        pos[y] = i
    ans = 0
    global tree
    tree = [0] * (4 * n)
    for i in range(n):
        cur = 1 + get(1, 0, n, pos[i])
        print("i = %s cur = %s pos[i] = %s" % (i, cur, pos[i]))
        ans += cur
        upd(1, 0, n, pos[i] + 1, n, cur)
    print(ans)
