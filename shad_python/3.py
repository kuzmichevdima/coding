def f(n):
    result = ''
    S = set()
    while n != 1:
        if n in S:
            return 'hypothesis is wrong'
        S.add(n)
        result += str(n) +  " -> "
        if n % 2 == 0:
            n = n // 2
        else:
            n = 3 * n + 1
    result += '1'
    return result
print(f(int(input())))
