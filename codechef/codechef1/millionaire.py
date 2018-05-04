T = int(input())
for test in range(T):
    n = int(input())
    right = input()
    chef = input()
    cnt = 0
    for i in range(n):
        if right[i] == chef[i]:
            cnt += 1
    w = [int(x) for x in input().split()]
    ans = w[cnt] if cnt == n else max(w[:cnt + 1])
    print(ans)
