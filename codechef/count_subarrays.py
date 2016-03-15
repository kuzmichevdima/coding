

test_count = int(input())
for test in range(test_count):
    n = int(input())
    a = [int(x) for x in input().split()]
    start = 0
    ans = 0
    for i in range(1, n + 1):
        if i == n or a[i] < a[i - 1]:
            L = i - start
            ans += L * (L + 1) // 2
            start = i
    print(ans)
