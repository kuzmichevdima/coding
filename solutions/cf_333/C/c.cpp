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

#define ld long double

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const int maxn = 105;
const int maxm = 1005;

int place[maxn];
ld pref_prev[maxm * maxn];
ld pref_cur[maxm * maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
/*    freopen("inp", "w", stdout);
    n = 100;
    m = 1000;
    printf("%d %d\n", n, m);
    forn(i, n)
        printf("%d\n", rand() % 5 + 1);
    exit(0);*/
    scanf("%d%d", &n, &m);
    int final_res = 0;
    forn(i, n)
    {
        scanf("%d", &place[i]);
        final_res += place[i];
    }
    fore(j, 1, m)
    {
        pref_prev[j] = pref_prev[j - 1] + (j == place[0] ? 0 : 1);
//        printf("pref_prev[%d] = %.5lf\n", j, pref_prev[j]);
    }
    fore(j, m + 1, n * m)
        pref_prev[j] = pref_prev[j - 1];
    ld coeff = 1.0 / (m - 1);
    fore(step, 1, n - 1)
    {
        memset(pref_cur, 0, sizeof(pref_cur));
        fore(sum, step + 1, n * m)
        {
//            fore(last, 1, m) if (last != place[step])
  //              e[step][sum] += e[step - 1][sum - last] * coeff;
            ld e = pref_prev[sum - 1];
            if (sum - m - 1 > 0)
                e -= pref_prev[sum - m - 1];
//            printf("before step = %d sum = %d e = %.5lf\n", step, sum, e);
            if (sum - place[step] > 0)
                e -= (pref_prev[sum - place[step]] - pref_prev[sum - place[step] - 1]);
            e *= coeff;
            printf("step = %d sum = %d e = %.5lf\n", step, sum, (double)e);
            pref_cur[sum] = pref_cur[sum - 1] + e;
        }
        memcpy(pref_prev, pref_cur, sizeof(pref_prev));
    }
    ld ans = 1.0 + pref_prev[final_res - 1];
    printf("%.12lf\n", (double)ans);
}
