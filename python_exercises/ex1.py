n = int(input())
a = [[abs(i - j) for j in range(n)] for i in range(n)]
print(a)
for i in range(n):
    print(' '.join(a[i]))
