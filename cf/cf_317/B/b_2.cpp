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

const int maxn = 3e5 + 5;
const int maxk = 5005;
const i64 inf = 1e18;

i64 prec[maxn][2];
int a[maxn];
int n, L, k;
i64 dp[maxk][maxk];

inline void upd(i64 & x, i64 y)
{
    x = min(x, y);
}

void precalc()
{
    //printf("precalc\n");
 //   for (int x : a) if (x != 0)
   //     printf("%d ", x);
    forn(i, L - 1)
        prec[0][0] += a[i + 1] - a[i];
    prec[0][1] = prec[0][0] + a[L] - a[L - 1];
    fore(pos, 1, n - L)
    {
        prec[pos][0] = prec[pos - 1][0] - (a[pos] - a[pos - 1]) + (a[pos + L - 1] - a[pos + L - 2]);
        prec[pos][1] = prec[pos][0] + (a[pos + L] - a[pos + L - 1]);
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    forn(j, n)
        scanf("%d", &a[j]);
    L = n / k;
//    printf("L = %d\n", L);
    sort(a, a + n);
    precalc();
    int second_typ = n % k;
    int first_typ = k - second_typ;
    fore(i, 0, first_typ)
        fore(j, 0, second_typ)
            dp[i][j] = inf;
    dp[0][0] = 0;
    fore(i, 0, first_typ)
        fore(j, 0, second_typ)
        {
            int pos = i * L + j * (L + 1);
            if (i < first_typ)
                upd(dp[i + 1][j], dp[i][j] + prec[pos][0]);
            if (j < second_typ)
                upd(dp[i][j + 1], dp[i][j] + prec[pos][1]);
        }
    cout << dp[first_typ][second_typ];
}

