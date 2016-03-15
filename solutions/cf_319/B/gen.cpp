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

const int maxn = 100;

bool a[maxn][maxn];
int n;
int p[maxn];

void go(int x, int y)
{
    if (x == n + 1)
    {
        int cnt = 0;
        fore(i, 1, n)
            fore(j, i + 1, n)
                if (a[i][j])
                {
                    if (!a[p[i]][p[j]] || cnt > n - 1)
                        return;   
                    cnt++;
                }
        if (cnt != n - 1)
            return;
        fore(i, 1, n)
            fore(j, i + 1, n) if (a[i][j])
                printf("%d %d\n", i, j);
        exit(0);
    }
    if (y == n + 1)
    {
        go(x + 1, 1);
        return;
    }
    if (x == y)
    {
        go(x, y + 1);
        return;
    }
    a[x][y] = a[y][x] = 0;
    go(x, y + 1);
    a[x][y] = a[y][x] = 1;
    go(x, y + 1);

}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    srand(time(0));
    n = 6;
    fore(j, 1, n)
        p[j] = j;
    random_shuffle(p + 1, p + n + 1);
    fore(j, 1, n)
        printf("%d ", p[j]);
    printf("\n");
    go(1, 2);
}
