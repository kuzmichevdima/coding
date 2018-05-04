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

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int bins, events;
    scanf("%d%d", &bins, &events);
    vi cur(bins);
    forn(i, bins)
        scanf("%d", &cur[i]);
    vector<pii> q(events);
    vector<vi> decr(bins);
    forn(i, events) {
        scanf("%d", &q[i].fi);
        if (q[i].fi == 1) {
            scanf("%d", &q[i].se);
            q[i].se--;
            decr[q[i].se].pb(i);
        }
    }
    set<pii> S;
    forn(i, bins) {
        fore(j, cur[i], (int)decr[i].size() - 1)
            S.insert({decr[i][j], i});
    }
    forn(i, events) {
        if (q[i].fi == 1) {
            continue;
        }
        int minn;
        if (!S.empty()) {
            minn = S.begin()->se;
            S.erase(S.begin());
        } else {
            minn = 0;
        }
        printf("%d\n", minn + 1);
    }
}

