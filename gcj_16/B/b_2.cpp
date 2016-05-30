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

const int maxn = 205;

double ans;

double dp[maxn][maxn];
int n, k;
double p[maxn];

void go(vi chosen) {
        memset(dp, 0, sizeof(dp));
        dp[0][1] = p[chosen[0]];
        dp[0][0] = 1 - dp[0][1];
//        printf("%.2lf %.2lf\n", dp[0][0], dp[0][1]);
        fore(i, 1, k - 1)
            forn(yes, i + 1) {
                dp[i][yes + 1] += dp[i - 1][yes] * p[chosen[i]];
                dp[i][yes] += dp[i - 1][yes] * (1 - p[chosen[i]]);
            }
 //       printf("dp[k - 1][0] = %.2lf dp[k - 1][1] = %.2lf\n", dp[k - 1][0], dp[k - 1][1]);
        if (dp[k - 1][k / 2] > ans) {
            ans = dp[k - 1][k / 2];
        }
}

int main() {
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        scanf("%d%d", &n, &k);
        forn(j, n)
            scanf("%lf", &p[j]);
        sort(p, p + n);
        ans = 0;
        forn(taken, k + 1) {
            vi chosen;
            forn(j, taken)
                chosen.pb(j);
            fore(j, n - (k - taken), n - 1)
                chosen.pb(j);
            go(chosen);
        }

        printf("Case #%d: %.10lf\n", test + 1, ans);
    }
}
