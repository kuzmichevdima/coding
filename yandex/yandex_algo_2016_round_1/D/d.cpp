#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>

using namespace std;

#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define fs first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const int maxn = 1e6;
const int MOD = 1e9+7;

i64 fact[maxn + 5];
i64 rev_fact[maxn + 5];

i64 binpow(i64 x, int p) {
    if (p == 0)
        return 1;
    i64 y = binpow(x, p / 2);
    y = y * y % MOD;
    if (p & 1)
        y = y * x % MOD;
    return y; 
}

void precalc() {
    fact[0] = 1;
    fore(i, 1, maxn)
        fact[i] = fact[i - 1] * i % MOD;
    forn(i, maxn + 1)
        rev_fact[i] = binpow(fact[i], MOD - 2);
}

i64 get_c(int n, int k) {
    return fact[n] * rev_fact[k] % MOD * rev_fact[n - k] % MOD;
}

i64 get_parts(int n, int k) {
    return get_c(n + k - 1, k - 1);
}

i64 solve(int m, int w, int p) {
    if (p == 0)  {
        if (w != 0 && m != 0) {
            return 0;
        } else return fact[w] * fact[m] % MOD;
    }
    if (p == 1) {
        i64 ans = fact[m] * fact[w] * 2 % MOD;
        return ans;
    }
    //i64 part1 = p * solve(m, w, p - 1) % MOD;
    //i64 part1 = 0;
    i64 part_m_first = 0, part_w_first = 0;
    if (m != 0) {
        int w_parts = (p + 1) / 2;
        int m_parts = p + 1 - w_parts;
        part_m_first = get_parts(w, w_parts) * get_parts(m - 1, m_parts) % MOD;
    }
    if (w != 0) {
        int m_parts = (p + 1) / 2;
        int w_parts = p + 1 - m_parts;
        part_w_first = get_parts(w - 1, w_parts) * get_parts(m, m_parts) % MOD;
    }
    return (part1 + part_w_first + part_m_first) % MOD;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int m, w, p;
    scanf("%d%d%d", &m, &w, &p);
    precalc();
    i64 result = 0;
    forn(j, p + 1)
        result = (result + solve(m - j, w - j, j)) % MOD;
    cout << result;
}
