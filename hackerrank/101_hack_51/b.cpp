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

const int maxn = 1e5+5;
const int DOWN = 0;
const int RIGHT = 1;
const int UP = 2;
const int LEFT = 3;

pii a[maxn];
int m, n;
const int inf = 1e9;

int side(pii p) {
    if (p.se == 0)
        return DOWN;
    if (p.fi == n)
        return RIGHT;
    if (p.se == n)
        return UP;
    return LEFT;
}

int dist(pii x, pii y) {
    vector <pii> vertex = {x, y, mp(0, 0), mp(n, 0), mp(n, n), mp(0, n)};
    vi dist(vertex.size(), inf);
    dist[0] = 0;
    vector<bool> marked(vertex.size());
    while(true) {
        int chosen = -1;
        forn(j, vertex.size()) {
            if (!marked[j] && (chosen == -1 || dist[j] < dist[chosen]))
                chosen = j;
        }
        if (chosen == -1 || dist[chosen] == inf)
            break;
        marked[chosen] = true;
        forn(an, vertex.size()) {
            if (marked[an])
                continue;
            if (vertex[chosen].fi != vertex[an].fi && vertex[chosen].se != vertex[an].se)
                continue;
            int newd;
            if (vertex[chosen].se == 0 && vertex[an].se == 0) {
                newd = vertex[an].fi - vertex[chosen].fi;
            }
            else if (vertex[chosen].fi == n && vertex[an].fi == n) {
                newd = vertex[an].se - vertex[chosen].se;
            }
            else if (vertex[chosen].se == n && vertex[an].se == n) {
                newd = vertex[chosen].fi - vertex[an].fi;
            }
            else if (vertex[chosen].fi == 0 && vertex[an].fi == 0) {
                newd = vertex[chosen].se - vertex[an].se;
            } else continue;
            if (newd < 0)
                continue;
            dist[an] = min(dist[an], dist[chosen] + newd);
        }
    }
    //printf("dist from %d %d to %d %d is %d\n", x.fi, x.se, y.fi, y.se, dist[1]);
    return dist[1];
}


int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int k;
    scanf("%d%d%d", &n, &m, &k);
    vector <vector <pii> > lst(4);
    forn(j, m) {
        scanf("%d%d", &a[j].fi, &a[j].se);
        int s = side(a[j]);
        lst[s].pb(a[j]);
    }
    forn(j, 4)
        sort(lst[j].begin(), lst[j].end());
    fore(j, 2, 3)
        reverse(lst[j].begin(), lst[j].end());
    vector <pii> order;
    forn(j, 4)
        for (pii p : lst[j])
            order.pb(p);
    //for (pii p : order)
      //  cout << p.fi << " " << p.se << endl;
    assert((int)order.size() == m);
    int ans = inf;
    forn(start, m) {
        int x = 0;
        int y = k - 1;
        while(x < y) {
            int middle = (x + y) / 2 + 1;
            if (order[(middle + start) % m] != order[start])
                x = middle;
            else y = middle - 1;
        }
        int fin = (start + x) % m;
        //fin = (start + k - 1) % m;
        /*while(fin != start && order[start] == order[fin]) {
            fin--;
            if (fin == -1)
                fin = m - 1;
        }*/
        int cur = dist(order[start], order[fin]);
        //printf("start = %d cur = %d\n", start, cur);
        ans = min(ans, cur);
    }
    cout << ans;
}

