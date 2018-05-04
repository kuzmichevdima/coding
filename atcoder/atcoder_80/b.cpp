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

const int maxn = 105;

int a[maxn][maxn];
int n, m;

bool move(pii& cur, pii change) {
    pii tmp = mp(cur.fi + change.fi, cur.se + change.se);
    if (tmp.fi < 0 || tmp.fi >= n || tmp.se < 0 || tmp.se >= m || a[tmp.fi][tmp.se] != 0)
        return false;
    cur = tmp;
    return true;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int c;
    scanf("%d%d%d", &n, &m, &c);
    pii cur = mp(0, 0);
    pii LEFT = mp(0, -1);
    pii RIGHT = mp(0, 1);
    pii DOWN = mp(1, 0);
    fore(j, 1, c) {
        int cnt;
        scanf("%d", &cnt);
        forn(iter, cnt) {
            a[cur.fi][cur.se] = j;
            //printf("iter = %d cur = %d %d\n", iter, cur.fi, cur.se);
            if (move(cur, RIGHT))
                continue;
            if (move(cur, LEFT))
                continue;
            move(cur, DOWN);
        }
    }
    forn(i, n) {
        forn(j, m)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

