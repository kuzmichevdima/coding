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
const int con = 2e5+5;
const int maxn = 2005;

int fact[con + 5];
int rev[con + 5];
int dp[maxn];
pii a[maxn];

int bin_pow(int x, int p)
{
    if (p == 0)
        return 1;
    int y = bin_pow(x, p / 2);
    y = (i64)y * y % MOD;
    if (p & 1)
        y = (i64)y * x % MOD;
    return y;
}

void precalc()
{
    fact[0] = fact[1] = 1;
    fore(i, 2, con)
        fact[i] = (i64)fact[i - 1] * i % MOD;
    forn(i, con + 1)
        rev[i] = bin_pow(fact[i], MOD - 2);
}

inline int C(int n, int k)
{
    return (i64)fact[n] * rev[k] % MOD * rev[n - k] % MOD;
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
    int black, n, m;
    scanf("%d%d%d", &n, &m, &black);
    forn(j, black)
        scanf("%d%d", &a[j].fi, &a[j].se);
    a[black].fi = n;
    a[black].se = m;
    sort(a, a + black + 1);
    forn(j, black + 1)
    {
        dp[j] = C(a[j].fi + a[j].se - 2, a[j].fi - 1);
        forn(prev, j)
            if (a[prev].fi <= a[j].fi && a[prev].se <= a[j].se)
            {
                int delta_x = a[j].fi - a[prev].fi;
                int delta_y = a[j].se - a[prev].se;
                int to_sub = (i64)dp[prev] * C(delta_x + delta_y, delta_x) % MOD;
                dp[j] = (dp[j] - to_sub + MOD) % MOD;
            }
//        printf("%d %d dp = %d\n", a[j].fi, a[j].se, dp[j]);
    }
    printf("%d", dp[black]);
}
