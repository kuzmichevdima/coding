def sums(lst):
    result = [0]
    for x in lst:
        result.append(x + result[-1])
    return result
a = [int(x) for x in input().split()]
print(sums(a))
