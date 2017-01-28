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

const int maxn = 305;
const int inf = 2e9;

int a[maxn];

int main() {
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        fprintf(stderr, "test %d\n", test);
        int n, m;
        scanf("%d%d", &n, &m);
        vi dp(n + 1, inf);
        dp[0] = 0;
        forn(i, n) {
            forn(j, m)
                scanf("%d", &a[j]);
            sort(a, a + m);
            int total = 0;
            vi next_dp(n + 1, inf);
            fore(add, 0, m) {
                fore(prev, i, n - add) if (dp[prev] != inf)
                    next_dp[prev + add] = min(next_dp[prev + add], dp[prev] + total + add * add);
                total += a[add];
            }
            dp = next_dp;
        }
        printf("Case #%d: %d\n", test + 1, dp[n]);
    }
}
