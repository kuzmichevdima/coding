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

const int maxn = 155;
const int inf = 1e9;

int a[maxn];
int dp_prev[maxn][maxn * maxn];
int dp_next[maxn][maxn * maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif  
    int n, k, s;
    scanf("%d%d%d", &n, &k, &s);
    forn(j, n)
        scanf("%d", &a[j]);
    if (s >= n * (n - 1) / 2)
    {
        sort(a, a + n);
        int ans = 0;
        forn(j, k)
            ans += a[j];
        printf("%d", ans);
        exit(0);
    }
    fore(got, 0, k)
        fore(used, 0, s)
            dp_prev[got][used] = inf;
    dp_prev[0][0] = 0;
    fore(pos, 0, n - 1)
    {
        memcpy(dp_next, dp_prev, sizeof(dp_prev));
/*        fore(got, 0, k)
            fore(used, 0, s)
                dp_next[got][next] = dp_prev[got][next];*/
        fore(got, 0, min(pos, k))
            fore(used, 0, s) if (dp_prev[got][used] != inf)
            {
               dp_next[got + 1][used + pos - got] = min(dp_next[got + 1][used + pos - got], dp_prev[got][used] + a[pos]);
            }
        memcpy(dp_prev, dp_next, sizeof(dp_next));
    }
    int ans = inf;
    fore(used, 0, s)
        ans = min(ans, dp_prev[k][used]);
    printf("%d", ans);
}
