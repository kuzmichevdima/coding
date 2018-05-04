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

#define ld double

const int maxn = 22;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};

ld prob[2][maxn][maxn];
char a[maxn][maxn];
pii start;
int n, m, k;
pii tunnel[maxn][maxn];
vector <pii>  list[maxn][maxn];

inline bool ok(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && a[x][y] != '#';
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d%d\n", &n, &m, &k);
    forn(i, n) {
        forn(j, m) {
            scanf("%c", &a[i][j]);
            if (a[i][j] == 'A') {
                a[i][j] = 'O';
                start = mp(i, j);
            }
            /*if (a[i][j] == '%') {
                a[i][j] = 'O';
                finish = mp(i, j);
            }*/
        }
        scanf("\n");
    }
    /*forn(i, n) {
        forn(j, m)
            printf("%c", a[i][j]);
        printf("\n");
    }*/
    forn(i, n)
        forn(j, m)
            tunnel[i][j] = mp(i, j);
    forn(j, k) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1--;
        y1--;
        x2--;
        y2--;
        tunnel[x1][y1] = mp(x2, y2);
        tunnel[x2][y2] = mp(x1, y1);
    }
    prob[0][start.fi][start.se] = 1;
    int cur = 0;
    ld answer = 0;
    forn(i, n)
        forn(j, m) if (a[i][j] == 'O') {
            forn(move, 4) {
                int i1 = i + dx[move];
                int j1 = j + dy[move];
                if (ok(i1, j1))
                    list[i][j].pb(tunnel[i1][j1]);
            }
        }

    forn(iter, 1e5) {
        memset(prob[1 - cur], 0, sizeof(prob[1 - cur]));
        forn(i, n)
            forn(j, m) if (a[i][j] == 'O') {
                if (!list[i][j].empty()) {
                    ld to_add = prob[cur][i][j] / list[i][j].size();
                    for (pii p : list[i][j])
                        prob[1 - cur][p.fi][p.se] += to_add;
                }
            } else if (a[i][j] == '%')
                answer += prob[cur][i][j];
        cur = 1 - cur;
    }
    printf("%.20lf\n", (double)answer);
}

