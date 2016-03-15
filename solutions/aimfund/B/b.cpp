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

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    int L = n / k;
    int small_cnt = k - n % k;
    int big_cnt = n % k;
    forn(j, n)
    {
        scanf("%d", &a[j]);
        repr[j] = mp(-1, -1);
        dp[j] = inf;
    }
    sort(a, a + n);
    dp[0] = 0;
    repr[0] = mp(0, 0);
    forn(i, n) if (repr[i].fi != -1)
    {
        if (repr[i].fi < small_cnt && i + L <= n)
        {
            dp[i + L] = min(dp[i + L], dp[i] + a[i + L - 1] - a[i]);
            repr[i + L] = mp(repr[i].fi + 1, repr[i].se);
        }
        if (repr[i].se < big_cnt && i + L + 1 <= n)
        {
            dp[i + L + 1] = min(dp[i + L + 1], dp[i] + a[i + L] - a[i]);
            repr[i + L + 1] = mp(repr[i].fi, repr[i].se + 1);
        }
    }
}
