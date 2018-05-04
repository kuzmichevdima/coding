def check(x, n):
    start = 0
    finish = n
    while start < finish:
        middle = (start + finish) // 2
        if middle * middle < x:
            start = middle + 1
        else:
            finish = middle
    return start * start == x
            

#T = int(input())
eps = 1.0e-9
#for i in range(T):
for n in range(1, 100):
    #n = int(input())
    found = False
    for i in range(1, n):
        L = n * n - i * i
        if L % 4 != 0:
            continue
        L = L // 4
        if check(L, n):
            found = True
            #print("%s YES i = %s L = %s" % (n, i, L))
            print("YES")
            break
    #print("YES" if found else "NO")
    if not found:
        print("NO")
        #print("%s NO" % n)
