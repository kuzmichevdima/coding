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

const int maxn = 2005;
const int mod = 1e9+7;

int prec[maxn][maxn];
char a[maxn][maxn];
int n, m;

void precalc() {
    forn(col, m) {
        prec[col][0] = 0;
        fore(row, 1, n - 1)
            prec[col][row] = prec[col][row - 1] + (a[row][col] == 't');
    }
}

int get(int col, int l, int r) {
    if (l < 0)
        l = 0;
    if (r > n - 1)
        r = n - 1;
    if (l > r)
        return 0;
    return prec[col][r] - (l == 0 ? 0 : prec[col][l - 1]);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d\n", &n, &m);
    m = 2 * m - 1;
    forn(i, n) {
        forn(j, m)
            scanf("%c", &a[i][j]);
        scanf("\n");
    }
    /*forn(i, n) {
        forn(j, m)
            printf("%c", a[i][j]);
        printf("\n");
    }*/
    precalc();
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int t;
        scanf("%d", &t);
        int ans = 0;
        fore(i, 1, n - 2)
            fore(j, 0, m - 1) if (a[i][j] != '#') {
                int cnt = 0;
                for (int col = 0; col < m; col += 2) if (col != j) {
                    int bound = min(n - i - 2, t - i - abs(col - j));
                    //printf("bound = %d\n", bound);
                    cnt += get(col, 1, bound);
                    int tmp = bound;
                    bound = max(n - i - 1, 2 * (n - 1) - i - t + abs(col - j));
                    bound = max(bound, tmp + 1);
                    cnt += get(col, bound, n - 2);
                }
                cnt += get(j, max(1, i - t), min(n - 2, i + t));
                //printf("i = %d j = %d cnt = %d\n", i, j, cnt);
                ans += (i64)cnt * cnt * (i + 1) * (j + 1) % mod;
                if (ans >= mod)
                    ans -= mod;
            }
        printf("%d\n", ans);
    }
}

