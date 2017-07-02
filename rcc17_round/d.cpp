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

inline i64 sqr(i64 x) {
    return x * x;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n;
        scanf("%d", &n);
        vi allx;
        vector <pii> a(n);
        forn(i, n) {
            scanf("%d%d", &a[i].fi, &a[i].se);
            a[i].fi *= 2;
            a[i].se *= 2;
            allx.pb(a[i].fi);
        }
        sort(allx.begin(), allx.end());
        allx.resize(unique(allx.begin(), allx.end()) - allx.begin());
        vector <vi> list(allx.size());
        forn(i, n)
            list[lower_bound(allx.begin(), allx.end(), a[i].fi) - allx.begin()].pb(a[i].se);
        forn(i, allx.size())
            sort(list[i].begin(), list[i].end());
        //for (int x : allx)
          //  printf("x = %d\n", x);
        i64 ans = (i64)n * (n - 1) * (n - 2) / 6;
        forn(i, n)
            fore(j, i + 1, n - 1) {
                int midx = ((i64)a[i].fi + a[j].fi) / 2;
                int midy  = ((i64)a[i].se + a[j].se) / 2;
                i64 r2 = sqr((i64)midx - a[i].fi) + sqr((i64)midy - a[i].se);
                i64 r = sqrt(r2);
                int x_start = lower_bound(allx.begin(), allx.end(), -r + midx) - allx.begin();
                int x_finish = upper_bound(allx.begin(), allx.end(), r + midx) - allx.begin();
                //printf("i = %d j = %d midx = %d midy = %d r = %lld %d %d\n", i, j, midx, midy, r, x_start, x_finish);
                fore(x_ind, x_start, x_finish - 1) {
                   i64 bound = sqrt(r2 - sqr(allx[x_ind] - midx));
                   /*for (int y : list[x_ind])
                       printf("%d ", y);
                   printf("\n");*/
                   int reduce = upper_bound(list[x_ind].begin(), list[x_ind].end(), bound + midy) -
                       lower_bound(list[x_ind].begin(), list[x_ind].end(), -bound + midy);
                   //printf("i = %d j = %d x = %d bound = %lld reduce = %d\n", i, j, allx[x_ind], bound, reduce);
                   ans -= reduce;
                }
                vi to_check;
                to_check.pb(i);
                to_check.pb(j);
                for (int h : to_check)
                    if (a[h].fi >= allx[x_start] && a[h].fi <= allx[x_finish - 1])
                        ans++;
                //printf("ans = %lld\n", ans);
            }
        cout << ans << endl;
    }
}

