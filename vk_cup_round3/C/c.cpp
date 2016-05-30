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

const int maxn = 1e5+5;
const int maxk = 55;
const double inf = 1e18;

double dp[maxn][maxk];
int a[maxn];

double get(int s, int f) {
    double res = 1;
    double cur_sum = a[s];
    fore(i, s + 1, f) {
        cur_sum += a[i];
        res += cur_sum / a[i];
    }
    return res;

}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    forn(i, n)
        scanf("%d", &a[i]);
    forn(i, n)
        forn(j, k + 1)
            dp[i][j] = inf;
    dp[0][1] = 1;
    fore(i, 1, n - 1)
        fore(parts, 1, min(k, i + 1)) {
            fore(start, 0, i) {
                double nnew = (start == 0 ? 0 : dp[start - 1][parts - 1]);
                nnew += get(start, i);
                dp[i][parts] = start == 0 ? nnew : min(dp[i][parts], nnew);
            }
        }
    printf("%.10lf\n", dp[n - 1][k]);

}
