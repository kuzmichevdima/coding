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
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};
const int inf = 2e9;

string s[maxn];
int d[maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(i, n)
        cin >> s[i];
    pii start, finish;
    scanf("%d%d%d%d", &start.fi, &start.se, &finish.fi, &finish.se);
    start.fi--;
    start.se--;
    finish.fi--;
    finish.se--;
    forn(i, n)
        forn(j, m)
            d[i][j] = inf;
    d[start.fi][start.se] = 0;
    set <pair<int, pii> > order;
    order.insert(mp(0, start));
    while(!order.empty()) {
        auto fr = *order.begin();
        order.erase(order.begin());
        pii v = fr.se;
        if (d[v.fi][v.se] != fr.fi) {
            continue;
        }
        forn(move, 4) {
            int x = v.fi + dx[move];
            int y = v.se + dy[move];
            if (x >= 0 && x < n && y >= 0 && y < m) {
                int newd = d[v.fi][v.se] + abs(s[v.fi][v.se] - s[x][y]);
                if (d[x][y] > newd) {
                    d[x][y] = newd;
                    order.insert(mp(d[x][y], mp(x, y)));
                }
            }
        }
    }
    printf("%d", d[finish.fi][finish.se]);
}

