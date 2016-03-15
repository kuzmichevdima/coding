tmp = [int(x) for x in input().split()]
n = tmp[0]
m = tmp[1]
start = [int(x) for x in input().split()]
tree = [0] * (n * 4)
#print("n = " + str(n) + " m = " + str(m))

def build(i, curL, curR):
    #print("i = " + str(i) + " curL = " + str(curL) + " curR = " + str(curR))
    if (curL == curR):
        tree[i] = start[curL - 1]
    else:
        middle = (curL + curR) // 2
        build(i * 2, curL, middle)
        build(i * 2 + 1, middle + 1, curR)
        tree[i] = tree[i * 2] + tree[i * 2 + 1]

build(1, 1, n)

def get(i, curL, curR, L, R):
    if R < curL or L > curR:
        return 0
    if curL == L and curR == R:
        return tree[i]
    middle = (curL + curR) // 2
    g1 = get(i * 2, curL, middle, L, min(R, middle))
    g2 = get(i * 2 + 1, middle + 1, curR, max(L, middle + 1), R)
    return g1 + g2

def update(i, curL, curR, pos, newVal):
    if curL == pos and curR == pos:
        tree[i] = newVal
        return
    middle = (curL + curR) // 2
    if (pos <= middle):
        update(i * 2, curL, middle, pos, newVal)
    else:
        update(i * 2 + 1, middle + 1, curR, pos, newVal)
    tree[i] = tree[i * 2] + tree[i * 2 + 1]

for iter in range(m):
    tmp = [int(x) for x in input().split()]
    typ = tmp[0]
    if typ == 1:
        pos = tmp[1]
        newVal = tmp[2]
        #print("update " + str(pos) + " " + str(newVal))
        update(1, 1, n, pos, newVal)
    else:
        start = tmp[1]
        finish = tmp[2]
        #print("get " + str(start) + " " + str(finish))
        answer = get(1, 1, n, start, finish)
        print(answer)

