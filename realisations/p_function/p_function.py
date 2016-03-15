def my_func():
    s = input()
    n = len(s)
    k = 0
    pi = [0] * n
    for i in range(1, n):
        while(k > 0 and s[k] != s[i]):
            k = pi[k - 1]
        if (s[k] == s[i]):
            k += 1
        pi[i] = k
    for x in pi:
        print(x, end = ' ')

my_func()

