def add(x, y):
    x += y
    if x >= MOD:
        x -= MOD
    return x

def precalc():
    C = [[] for i in range(k + 1)]
    C[0] = [0] * (k + 1)
    C[0][0] = 1
    C[1] = [0] * (k + 1)
    C[1][0] = C[1][1] = 1
    for i in range(2, k + 1):
        C[i] = [0] * (k + 1)
        for j in range(i + 1):
            C[i][j] = 1 if j == 0 else (C[i - 1][j - 1] + C[i - 1][j]) % MOD
    S = [0] * (k + 1)
    val = [0] * (k + 2)
    for i in range(1, k + 2):
        mult = 1
        tmp = 0
        for j in range(0, i):
            tmp += C[i - 1][j] * (i - j) * mult
            mult *= -1
        val[i] = tmp

    for kk in range(1, k + 1):
        prec = [x ** kk % MOD for x in range(kk + 2)]
        C_n_i = 1
        for i in range(1, kk + 2):
            if kk > 1:
                val[i] *= 
            C_n_i = C_n_i * (n - i + 1) // i
            addit = tmp * C_n_i % MOD
            #print(kk, i, C_n_i, tmp, addit)
            S[kk] = add(S[kk], addit)
    return S

def norm(x):
    while x <= 0:
        x += MOD
    if x >= MOD:
        x -= MOD
    return x

n, k, MOD = map(int, input().split())
S = precalc()
#print(S)
cur = [0] * (k + 1)
cur[1] = 1
ans = 0
for L in range(1, k + 1):
    for p in range(1, k + 1):
        ans = add(ans, S[p] * cur[p] % MOD)
    nnew = [0] * (k + 1)
    for j in range(1, k + 1):
        nnew[j] = norm(cur[j - 1] - L * cur[j])
    cur = nnew
print(ans)
