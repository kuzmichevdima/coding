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

const char order[4] = {'D', 'L', 'R', 'U'};
const int dx[4] = {1, 0, 0, -1};
const int dy[4] = {0, -1, 1, 0};
int n, m, k;
pii cur;
int dist[maxn][maxn];
char a[maxn][maxn];

inline bool ok(pii p) {
    return p.fi >= 0 && p.fi < n && p.se >= 0 && p.se < m && a[p.fi][p.se] != '*';
}

void get_dist() {
    forn(i, n)
        forn(j, m)
            dist[i][j] = -1;
    dist[cur.fi][cur.se] = 0;
    queue <pii> Q;
    Q.push(cur);
    while(!Q.empty()) {
        pii v = Q.front();
        Q.pop();
        forn(move, 4) {
            pii u = mp(v.fi + dx[move], v.se + dy[move]);
            if (ok(u) && dist[u.fi][u.se] == -1) {
                dist[u.fi][u.se] = dist[v.fi][v.se] + 1;
                Q.push(u);
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    scanf("%d%d%d\n", &n, &m, &k);
    forn(i, n) {
        forn(j, m) {
            scanf("%c", &a[i][j]);
            if (a[i][j] == 'X') {
                a[i][j] = '.';
                cur = mp(i, j);
            }
        }
        scanf("\n");
    }
    get_dist();
    /*forn(i, n) {
        forn(j, m)
            printf("%d ", dist[i][j]);
        printf("\n");
    }*/
    vector <char> ans;
    while(dist[cur.fi][cur.se] < k) {
        bool found = false;
        forn(move, 4) {
            pii nnew = mp(cur.fi + dx[move], cur.se + dy[move]);
            if (ok(nnew)) {
                ans.pb(order[move]);
                cur = nnew;
                k--;
                found = true;
                break;
            }
        }
        if (!found)
            break;
    }
    while (dist[cur.fi][cur.se] != 0 && k > 0) {
        forn(move, 4) {
            pii nnew = mp(cur.fi + dx[move], cur.se + dy[move]);
            if (ok(nnew) && dist[nnew.fi][nnew.se] == dist[cur.fi][cur.se] - 1) {
                ans.pb(order[move]);
                cur = nnew;
                k--;
                break;
            }
        }
    }
    if (k != 0 || dist[cur.fi][cur.se] != 0) {
        printf("IMPOSSIBLE");
        exit(0);
    }
    for (char c : ans)
        printf("%c", c);
}

