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

i64 b_sum[maxn];
int a[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n, m, x;
        scanf("%d%d%d", &n, &m, &x);
        forn(i, n)
            scanf("%d", &a[i]);
        forn(j, m) {
            int x;
            scanf("%d", &x);
            b_sum[j + 1] = b_sum[j] + x;
        }
        int sum = 0;
        int ans = 0;
        forn(take1, n + 1) {
            if (sum > x)
                break;
            int cur = take1 + upper_bound(b_sum, b_sum + m + 1, x - sum) - b_sum - 1;
 //           printf("take1 = %d cur = %d\n", take1, cur);
            ans = max(ans, cur);
            sum += a[take1];
        }
        printf("%d\n", ans);
    }
}
