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

const int inf = 1e9;
vector<pii> v[2];
int C[2];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d%d%d", &n, &C[0], &C[1]);
    forn(j, n) {
        int b, cost;
        char typ;
        scanf("%d%d %c", &b, &cost, &typ);
        //cerr << typ << endl;
        if (typ == 'C')
            v[0].pb(mp(cost, b));
        else v[1].pb(mp(cost, b));
    }
    forn(j, 2)
        sort(v[j].begin(), v[j].end());
    int ans = 0;
    forn(i, 2) {
        vi maxx(v[i].size());
        forn(j, v[i].size())
            maxx[j] = (j == 0 ? v[i][0].se : max(maxx[j - 1], v[i][j].se));
        int cur = -1;
        for (int second = (int)v[i].size() - 1; second > cur; second--) {
            int first_incorrect = upper_bound(v[i].begin(), v[i].begin() + second, mp(C[i] - v[i][second].fi, inf)) - v[i].begin();
            if (first_incorrect != 0)
                ans = max(ans, v[i][second].se + maxx[first_incorrect - 1]);
            //printf("%d %d\n", v[i][second].fi, v[i][second].se);
        }
    }
    cerr << "first part " << ans << endl;
    vi diff(2);
    forn(i, 2) {
        for (pii x : v[i])
            if (x.fi <= C[i])
                diff[i] = max(diff[i], x.se);
    }
    if (diff[0] != 0 && diff[1] != 0)
        ans = max(ans, diff[0] + diff[1]);
    printf("%d", ans);
}

