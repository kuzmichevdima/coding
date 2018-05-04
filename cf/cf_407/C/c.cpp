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


const int limit = 1e6+5;
const int inf = 1e9;

typedef int myarr[limit + 5];

myarr a, b;

void dp(myarr & dp, vi & v) {
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    forn(j, limit + 1)
        dp[j] = inf;
    dp[0] = 0;
    for (int x : v) {
        fore(i, 0, x * 999)
            if (dp[i] != inf && dp[i + x] > dp[i] + 1)
                dp[i + x] = dp[i] + 1;
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
    int n, k;
    scanf("%d%d", &n, &k);
    vi positive, negative;
    forn(j, k) {
        int x;
        scanf("%d", &x);
        if (x == n) {
            printf("1");
            exit(0);
        }
        if (x > n)
            negative.pb(x - n);
        else positive.pb(n - x);
    }
    if (positive.empty() || negative.empty()) {
        printf("-1");
        exit(0);
    }
/*    for (int x : positive)
        printf("%d ", x);
    printf("\n");
    for (int x : negative)
        printf("%d ", x);*/
    dp(a, positive);
    dp(b, negative);
    int ans = inf;
    fore(j, 1, limit)
        ans = min(ans, a[j] + b[j]);
    printf("%d", ans);
}
