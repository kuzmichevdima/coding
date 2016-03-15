def f(lst, a, b):
    return list(map(lambda x : a if x < a else (b if x > b else x), lst))
lst = [int(x) for x in input().split()]
a, b = [int(x) for x in input().split()]
print(f(lst, a, b))
