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

typedef pair<pii, int> elem;

const int maxn = 1005;
const int inf = 1e9;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};

int d[maxn][maxn][4];
char a[maxn][maxn];
int n, m;


bool ok(pii next) {
    return next.fi >= 0 && next.fi < n && next.se >= 0 && next.se < m && a[next.fi][next.se] == '.';
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    pii start, finish;
    scanf("%d%d\n", &n, &m);
    forn(i, n) {
        forn(j, m) {
            scanf("%c", &a[i][j]);
            if (a[i][j] == 'S') {
                start = mp(i, j);
                a[i][j] = '.';
            } else if (a[i][j] == 'T') {
                finish = mp(i, j);
                a[i][j] = '.';
            }
        }
        scanf("\n");
    }
    cerr << start.fi << " " << start.se << " " << finish.fi << " " << finish.se << endl;
    deque <elem> order;
    forn(i, n)
        forn(j, m)
            forn(k, 4)
                d[i][j][k] = inf;
    forn(move, 4) {
        order.push_back(mp(start, move));
        d[start.fi][start.se][move] = 0;
    }
    while(!order.empty()) {
        elem v = order.front();
        order.pop_front();
        pii pos = v.fi;
        pii next = mp(pos.fi + dx[v.se], pos.se + dy[v.se]);
        if (ok(next)) {
            if (d[pos.fi][pos.se][v.se] < d[next.fi][next.se][v.se]) {
                d[next.fi][next.se][v.se] = d[pos.fi][pos.se][v.se];
                order.push_front(mp(next, v.se));
            }
        }
        forn(move, 4) if (move != v.se) {
            if (d[pos.fi][pos.se][move] > d[pos.fi][pos.se][v.se] + 1) {
                d[pos.fi][pos.se][move] = d[pos.fi][pos.se][v.se] + 1;
                order.push_back(mp(pos, move));
            }
        }
    }
    cerr << d[2][4][3] << endl;
    int ans = inf;
    forn(move, 4)
        ans = min(ans, d[finish.fi][finish.se][move]);
    cerr << ans << endl;
    if (ans <= 2)
        printf("YES");
    else printf("NO");
}
