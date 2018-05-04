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

const int maxn = 605;

int a[maxn][maxn];
int ans[maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, shiftx, shifty;
    scanf("%d%d%d%d", &n, &m, &shiftx, &shifty);
    forn(i, n + shiftx)
        forn(j, m + shifty)
            scanf("%d", &a[i][j]);
    forn(i, n) {
        forn(j, m) {
            if (i < shiftx || j < shifty)
                ans[i][j] = a[i][j];
            else ans[i][j] = a[i][j] - ans[i - shiftx][j - shifty];
        }
    }
    forn(i, n) {
        forn(j, m)
            printf("%d ", ans[i][j]);
        printf("\n");
    }
}

