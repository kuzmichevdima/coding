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

const int maxn = 18;

bool wall[maxn][maxn];
bool found;
int n, m;

struct Pos
{
    int x, y, side;
    Pos() {}
    Pos(int x, int y, int side) : x(x), y(y), side(side) {}
    void print() {
        printf("%d %d %d\n", x, y, side);
    }
};
Pos a[maxn * maxn];
pii p[maxn * maxn];

bool operator < (Pos first, Pos second) {
    if (first.x != second.x)
        return first.x < second.x;
    if (first.y != second.y)
        return first.y < second.y;
    return first.side < second.side;
}

set <Pos> vis;


void dfs(Pos v) {
    if (vis.find(v) != vis.end())
        return;
    vis.insert(v);
    if (v.x < 0 || v.x >= n || v.y < 0 && v.side == 0 || v.y >= m && v.side == 1)
        return;
    printf("dfs\n");
    v.print();
    if (v.side == 0) {
        if (wall[v.x][v.y] == 1) {
            dfs(Pos(v.x, v.y, 1));
        } else dfs(Pos(v.x + 1, v.y, 1));
        if (v.y > 0) {
            if (wall[v.x][v.y - 1] == 1) {
                dfs(Pos(v.x + 1, v.y - 1, 1)); 
            } else dfs(Pos(v.x, v.y - 1, 1));
        }
    } else {
        if (wall[v.x][v.y] == 1) {
            dfs(Pos(v.x, v.y, 0));
        } else dfs(Pos(v.x, v.y + 1, 0));
        if (v.x > 0) {
            if (wall[v.x - 1][v.y] == 1) {
                dfs(Pos(v.x - 1, v.y + 1, 0)); 
            } else dfs(Pos(v.x - 1, v.y, 0));
        }

    }
}

void go(int i, int j) {
    if (found)
        return;
    if (i == n && j == 0) {
        printf("check\n");
        forn(i, n) {
                forn(j, m)
                    printf("%c", wall[i][j] ? '/' : '\\');
                printf("\n");
            }

        bool fail = false;
        forn(i, m + n) {
            vis.clear();
            dfs(a[p[i].fi]);
            printf("first = %d second = %d\n", p[i].fi, p[i].se);
            if (vis.find(a[p[i].se]) == vis.end()) {
                fail = true;
                break;
            }
            forn(an, m + n) if (i != an)
                if (vis.find(a[p[an].fi]) != vis.end() || vis.find(a[p[an].se]) != vis.end()) {
                    fail = true;
                    printf("an = %d\n", an);
                    break;
                }
            if (fail)
                break;
        }
        printf("fail  =%d\n", fail);
        if (!fail) {
            forn(i, n) {
                forn(j, m)
                    printf("%c", wall[i][j] ? '/' : '\\');
                printf("\n");
            }
            found = true;
        }
        return;
    }
    int i1 = i;
    int j1 = j + 1;
    if (j == n - 1) {
        i1 = i + 1;
        j1 = 0;
    }
    wall[i][j] = 0;
    go(i1, j1);
    wall[i][j] = 1;
    go(i1, j1);
}

int main() {
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        scanf("%d%d", &n, &m);
        forn(i, n + m) {
            scanf("%d%d", &p[i].fi, &p[i].se);
        }
        fore(i, 1, m)
            a[i] = Pos(0, i - 1, 1);
        fore(i, m + 1, m + n)
            a[i] = Pos(i - m - 1, m, 0);
        fore(i, m + n + 1, 2 * m + n)
            a[i] = Pos(n, i - m - n - 1, 1);
        fore(i, 2 * m + n + 1, 2 * m + 2 * n)
            a[i] = Pos(i - 2 * m - n - 1, 0, 0);
        fore(i, 1, 4)
            a[i].print();
        found = false;
        printf("Case #%d:\n", test + 1);
        go(0, 0);
        if (!found)
            printf("IMPOSSIBLE\n");
    }
}
