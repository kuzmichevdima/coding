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

const int maxn = 105;
const int maxm = 1005;

int place[maxn];
double e[maxn][maxm * maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    int final_res = 0;
    forn(i, n)
    {
        scanf("%d", &place[i]);
        final_res += place[i];
    }
    fore(j, 1, m)
        e[0][j] = (j == place[0] ? 0 : 1);
    double coeff = 1.0 / (m - 1);
    fore(step, 1, n - 1)
        fore(sum, step + 1, (step + 1) * m)
        {
            fore(last, 1, m) if (last != place[step])
                e[step][sum] += e[step - 1][sum - last] * coeff;
            printf("e[%d][%d] = %.5lf\n", step, sum, e[step][sum]);
        }
    double ans = 0;
    fore(sum, n, final_res - 1)
        ans += e[n - 1][sum];
    printf("%.10lf\n", ans);
}
