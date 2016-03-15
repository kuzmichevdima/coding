s = input()
n = len(s)
z = [0] * n
z[0] = n
l = -1
r = -1
for i in range(1, n):
	
    if (i <= r):
        z[i] = min(z[i - l], r - i + 1)
    while(i + z[i] < n and s[z[i]] == s[i + z[i]]):
        z[i] += 1
    if (z[i] != 0 and i + z[i] - 1 > r):
        l = i
        r = i + z[i] - 1
    print(str(i) + "z " + str(l) + " " + str(r))
	
for x in z:
    print(x, end = ' ')


