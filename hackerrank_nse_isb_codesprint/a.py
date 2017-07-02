from __future__ import print_function

n = int(input())
stma_len = 60
ltma_len = 300
p = [int(x) for x in raw_input().split()]

def get(lower, upper):
    return round(sum(p[lower: upper]) * 1. / (upper - lower), 2)

for i in range(ltma_len, n):
    cur_stma = get(i - stma_len + 1, i + 1)
    cur_ltma = get(i - ltma_len + 1, i + 1)
    prev_stma = get(i - stma_len, i)
    prev_ltma = get(i - ltma_len, i)
    f1 = prev_stma > prev_ltma and cur_stma <= cur_ltma
    f2 = prev_stma < prev_ltma and cur_stma >= cur_ltma
    f3 = prev_stma == prev_ltma and cur_stma != cur_ltma
    if f1 or f2 or f3:
        print(i + 1, cur_stma, cur_ltma, sep=' ')
