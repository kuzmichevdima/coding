#T = int(input())
#for test in range(T):
#    n = int(input())
for n in range(2, 100):
    j = 2
    found = False
    while j * j <= n:
        if n % j == 0:
            if j % 4 == 1 or (n // j) % 4 == 1:
                found = True
                break
        j += 1
    #if found:
    print("%s YES" % (n) if found else "%s NO" % (n))
