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


int ans = 0, n;

bool a[101][101];
int c[101];

void go(int x, int y)
{
    if (x == n + 1)
    {
        int cnt = 0;
        fore(i, 1, n) if (a[i][i])
        {
            cnt++;
        }
        if (cnt == n)
            return;
        assert(n != 3 || a[1][1] == 0 || a[2][2] == 0 || a[3][3] == 0);
        fore(i, 1, n)
            fore(j, 1, n) if (a[i][j] != a[j][i])
                return;
        fore(i, 1, n)
            fore(j, 1, n)
                fore(k, 1, n) if (a[i][j] && a[j][k] && !a[i][k])
                    return;
        ans++;
        printf("ans = %d\n", ans);
        c[cnt]++;
        fore(i, 1, n)
            fore(j, 1, n) if (a[i][j])
                printf("%d %d\n", i, j);
        return;
    }
    if (y == n + 1)
        go(x + 1, 1);
    else
    {
        a[x][y] = 1;
        go(x, y + 1);
        a[x][y] = 0;
        go(x, y + 1);
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    for (n = 1; n <= 4; n++)
    {
        memset(c, 0, sizeof(c));
        ans = 0;
        go(1, 1);
        printf("n = %d ans = %d\n", n, ans);
        fore(j, 1, n)
            printf("c[%d] = %d\n", j, c[j]);
    }
}

