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

const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};

const int maxn = 1005;
const int inf = 1e9;

int d[maxn][maxn][4];
vector <pii> list[4];
deque <pii> Q;
int a[maxn][maxn];
int n, m;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d\n", &n, &m);
    forn(i, n)
    {
        forn(j, m)
        {
            char c;
            scanf("%c", &c);
            if (c == '#')
                a[i][j] = -1;
            else if (c == '.')
                a[i][j] = 0;
            else
            {
                a[i][j] = c - '0';
                list[a[i][j]].pb(mp(i, j));
            }
        }
        scanf("\n");
    }
/*    forn(i, n)
    {
        forn(j, m)
            printf("%d ", a[i][j]);
        printf("\n");
    }*/
    fore(color, 1, 3)
    {
        forn(h, n)
            forn(g, m)
                d[h][g][color] = inf;
        for (pii p : list[color])
        {
            Q.push_back(p);
            d[p.fi][p.se][color] = 0;
        }
        while(!Q.empty())
        {
            pii p = Q.front();
            Q.pop_front();
            forn(move, 4)
            {
                int newx = p.fi + dx[move];
                int newy = p.se + dy[move];
                if (newx >= 0 && newx < n && newy >= 0 && newy < m && a[newx][newy] != -1)
                {
                    bool f = (a[p.fi][p.se] == 0 || a[newx][newy] == 0);
                    int newd = d[p.fi][p.se][color] + f;
                    if (newd < d[newx][newy][color])
                    {
                        d[newx][newy][color] = newd;
                        if (f)
                            Q.push_back(mp(newx, newy));
                        else Q.push_front(mp(newx, newy));
                    }
                }
            }
        }
    }
    int ans = inf;
    forn(x, n)
        forn(y, m) if (d[x][y][1] != inf && d[x][y][2] != inf && d[x][y][3] != inf)
        {
            int new_res = max(d[x][y][1] - 1, 0) + max(d[x][y][2] - 1, 0) + max(d[x][y][3] - 1, 0);
            if (a[x][y] == 0)
                new_res++;
//            printf("x = %d y = %d d1 = %d d2 = %d d3 = %d new_res = %d\n", x, y, d[x][y][1], d[x][y][2], d[x][y][3], new_res);
            ans = min(ans, new_res);
        }
    if (ans == inf)
        ans = -1;
    printf("%d", ans);
}
