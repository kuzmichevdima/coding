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

const int maxn = 705;
const i64 inf = 1e18;

int a[maxn][maxn];
i64 dp[maxn][maxn];

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
        int n;
        scanf("%d", &n);
        forn(i, n) {
            forn(j, n)
                scanf("%d", &a[i][j]);
            sort(a[i], a[i] + n);
        }
        forn(j, n)
            dp[0][j] = a[0][j];
        fore(i, 1, n - 1) {
            i64 maxx = -inf;
            int pointer = 0;
            forn(j, n) {
                while(pointer < n && a[i - 1][pointer] < a[i][j]) {
                    maxx = max(maxx, dp[i - 1][pointer]);
                    pointer++;
                }
                dp[i][j] = maxx == -inf ? -inf : maxx + a[i][j];       
            }
        }
        i64 ans = -inf;
        forn(i, n)
            ans = max(ans, dp[n - 1][i]);
        if (ans == -inf)
            ans = -1;
        cout << ans << endl;
    }
}

