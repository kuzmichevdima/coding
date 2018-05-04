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

const int MOD = 1e9+7;
const int maxn = 5e5;
int fact[maxn + 5];
int rev_fact[maxn + 5];
int npow[maxn + 5];

int bin_pow(int x, int p) {
    if (p == 0)
        return 1;
    int y = bin_pow(x, p / 2);
    y = (i64)y * y % MOD;
    return p % 2 == 0 ? y : (i64)y * x % MOD;
}

void precalc() {
    fact[0] = 1;
    fore(j, 1, maxn)
        fact[j] = (i64)fact[j - 1] * j % MOD;
    forn(j, maxn + 1)
        rev_fact[j] = bin_pow(fact[j], MOD - 2);
}

int c(int n, int k) {
    return ((i64)fact[n] * rev_fact[k] % MOD * rev_fact[n - k]) % MOD;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    precalc();
    int q;
    scanf("%d", &q);
    forn(query, q) {
        int m, n;
        scanf("%d%d", &m, &n);
        int ans = 0;
        int mult = 1;
        npow[0] = 1;
        fore(j, 1, m)
            npow[j] = (i64)npow[j - 1] * (n - 1) % MOD;
        for (int last = m; last >= n; last--) {
            ans = ((i64)c(last - 1, n - 1) * mult % MOD * npow[last - n] + ans) % MOD;
            mult = (i64)mult * n % MOD;
        }
        printf("%d\n", ans);
    }

}
