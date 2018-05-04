n = int(input())
a = [int(x) for x in input().split()]
a = sorted(a)
#print(a)
ans = 0
for j in range(n):
    ans += 2 ** j * a[n - j - 1]
print(ans)
