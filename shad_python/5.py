def primes(x):
    result = []
    d = 2
    while d * d <= x:
        cnt = 0
        while x % d == 0:
            x //= d
            cnt += 1
        if cnt:
            result.append([d, cnt])
        d += 1
    if x != 1:
        result.append([x, 1])
    return result
print(primes(int(input())))
