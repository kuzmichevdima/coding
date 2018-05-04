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

const int maxn = 1005;

i64 a[maxn][maxn];
i64 column[maxn];
i64 global[maxn][maxn];
i64 diag[2 * maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, q;
    scanf("%d%d", &n, &q);
    forn(i, q) {
        int startx, starty, L, delta;
        scanf("%d%d%d%d", &startx, &starty, &L, &delta);
        global[startx][starty] += delta;
        int finalx = startx + L;
        if (finalx <= n)
            global[finalx][starty] -= delta;
        /*int finaly = min(n, starty + L);
        int x = startx;
        fore(y, starty + 1, finaly) {
            a[x][y] -= delta;
            ++x;
        }*/
        int diag_num = startx - starty - 1 + n;
        diag[diag_num][startx] -= delta;
        if (finalx <= n)
            diag[diag_num][finalx] += delta;
        //printf("diag_num = %d startx = %d finalx = %d\n", diag_num, startx, finalx);
        /*int y = starty;
        fore(x, startx, min(n, startx + L - 1)) {
            
        }*/
    }
    fore(diag_num, -n, n) {
        i64 cur = 0;
        fore(x, 1, n) {
            int y = x - diag_num;
            //if (y >= 1 && y <= n)
            cur += diag[diag_num + n][x];
            //if (diag_num == -1)
            //    printf("x = %d y = %d cur = %lld\n", x, y, cur);
            if (y >= 1 && y <= n)
                a[x][y] += cur;
        }
    }
    fore(x, 1, n) {
        i64 cur = 0;
        fore(y, 1, n) {
            column[y] += global[x][y];
            cur += a[x][y] + column[y];
            cout << cur << " ";
        }
        printf("\n");
    }
}

