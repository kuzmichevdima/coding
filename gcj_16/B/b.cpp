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

vi chosen;
double ans;

double dp[18][18];
int n, k;
double p[18];

void go(int cur, int taken) {
    if (cur == n) {
        if (taken != k)
            return;
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
            printf("\ngo\n");
            for (int x : chosen) {
                printf("%d ", x);
            }
        }
        return;
    }
    if (taken != k) {
        chosen.pb(cur);
        go(cur + 1, taken + 1);
        chosen.pop_back();
    }
    go(cur + 1, taken);
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
        go(0, 0);
        printf("\n");
        forn(j, n)

            printf("%.2lf ", p[j]);
        printf("\n");
        printf("Case #%d: %.10lf\n", test + 1, ans);
    }
}
