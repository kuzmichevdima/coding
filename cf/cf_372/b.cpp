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
const i64 inf = 1e18;

bool mark[maxn];
i64 d[maxn];
i64 e[maxn][maxn];
//i64 floyd[maxn][maxn];

vector <pii> outp;

int n, start, finish;

/*void precalc() {
    fore(i, 1, n)
        fore(j, 1, n)
            floyd[i][j] = e[i][j];
    fore(i, 1, n)
        fore(j, 1, n)
            fore(k, 1, n) if (floyd[j][i] != inf && floyd[i][k] != inf) {
                floyd[j][k] = min(floyd[j][k], floyd[j][i] + floyd[i][k]);
            }
}*/

i64 get_d(int chosen) {
    fore(i, 0, n)
        d[i] = inf;
    d[start] = 0;
    memset(mark, false, sizeof(mark));
    while(true) {
        int best = -1;
        fore(i, 0, n) if (!mark[i] && d[i] < inf && (best == -1 || d[i] < d[best]))
            best = i;
        if (best == -1)
            break;
        mark[best] = true;
        fore(j, 0, n) if (e[best][j] != inf)
            d[j] = min(d[j], d[best] + (e[best][j] == 0 ? chosen : e[best][j]));
    }
    return d[finish];
}

void print(int chosen) {
    printf("YES\n");
    for (pii p : outp)
        printf("%d %d %d\n", p.fi, p.se, e[p.fi][p.se] == 0 ? chosen : (int)e[p.fi][p.se]); 
    exit(0);
}


vector <pii> Q;
int W;

i64 get(int m) {
    forn(num, Q.size()) {
        int u = Q[num].fi;
        int v = Q[num].se;
        if (num < m)
            e[v][u] = e[u][v] = W + 1;
        else e[v][u] = e[u][v] = W;
    }
    return get_d(W);

}

bool mycmp(pii first, pii second) {
    return min(d[first.fi], d[first.se]) < min(d[second.fi], d[second.se]);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int m, L;
    scanf("%d%d%d%d%d", &n, &m, &L, &start, &finish);
    fore(i, 0, n)
        fore(j, 0, n)
            e[i][j] = inf;
    outp.resize(m);
    forn(j, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
//        printf("%d %d %d\n", u, v, w);
        e[u][v] = e[v][u] = w;
        outp[j] = mp(u, v);
        if (w == 0)
            Q.pb(mp(u, v));
    }

    //precalc();

    int s = 1;
    int f = L + 1;
    while(s < f) {
        int m = (s + f) / 2 + 1;
        if (get_d(m) > L)
            f = m - 1;
        else s = m;
    }
    W = s;
//    printf("W = %d\n", W);
    if (W == L + 1) {
        if (get_d(1) == L) {
            print(1);
        } else printf("NO");
        exit(0);
    }
    if (L - get_d(W) < 0) {
        printf("NO");
        exit(0);
    }

    sort(Q.begin(), Q.end(), mycmp);
//    for (pii p : Q)
  //      printf("%d %d\n", p.fi, p.se);
    s = 0;
    f = Q.size();
    while(s < f) {
        int m = (s + f) / 2 + 1;
        if (get(m) > L)
            f = m - 1;
        else s = m;
    }
    get(s);
    print(-1);
    /*    fore(i, 1, n) 
        fore(j, i + 1, n) {
            if (e[i][j] == 0 && floyd[i][j] > w) {
                e[i][j] = e[j][i] = w + min(diff, floyd[i][j] - w);
                diff -= min(diff, floyd[i][j] - w);
            }
        }*/
    
}

