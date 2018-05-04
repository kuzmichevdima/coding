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

#define ld long double

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const ld inf = 1e18;
const ld eps = 1e-12;

typedef pair<ld, ld> mypair;

mypair get(int X1, int X2, int X0, int vx) {
    if (vx == 0) {
        if (X0 > X1 && X0 < X2)
            return mp(0, inf);
        else {
            printf("-1");
            exit(0);
        }
    }
    ld lower = (ld)(X1 - X0) / vx;
    ld upper = (ld)(X2 - X0) / vx;
    if (vx < 0)
        swap(lower, upper);
    lower = max(lower, (ld)0.);
    return mp(lower, upper);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, X1, Y1, X2, Y2;
    scanf("%d", &n);
    scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
    ld start = -inf;
    ld finish = inf;
    forn(j, n) {
        int X0, Y0, vx, vy;
        scanf("%d%d%d%d", &X0, &Y0, &vx, &vy);
        mypair tx = get(X1, X2, X0, vx);
        mypair ty = get(Y1, Y2, Y0, vy);
        printf("tx = %.15lf %.15lf ty = %.15lf %.15lf\n", (double)tx.fi, (double)tx.se, (double)ty.fi, (double)ty.se);
        ld minn = min(tx.se, ty.se);
        ld maxx = max(tx.fi, ty.fi);
        if (maxx - minn >= -eps) {
            printf("-1");
            exit(0);
        }
        start = max(start, maxx);
        finish = min(finish, minn);
    }
    printf("start = %.15lf finish = %.15lf diff = %.15lf\n", (double)start, (double)finish, (double)(finish - start));
    if (start - finish >= -eps) {
        printf("-1");
        exit(0);
    }
    printf("%.10lf", (double)start);
}
