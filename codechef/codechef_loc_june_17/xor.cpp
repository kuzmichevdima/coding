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

int a[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, queries;
    scanf("%d%d", &n, &queries);
    vector<pii> steps;
    steps.pb(mp(1, 0));
    forn(q, queries) {
        int typ;
        scanf("%d", &typ);
        if (typ == 1) {
            int pos, val;
            scanf("%d%d", &pos, &val);
            a[pos] = val;
            int cur_or = 0;
            steps.clear();
            fore(j, 1, n) {
                int new_or = cur_or | a[j];
                if (new_or != cur_or) {
                    steps.pb(mp(j, new_or));
                    cur_or = new_or;
                }
            }
        } else {
            int target;
            scanf("%d", &target);
            int cur = (int)steps.size() - 1;
            bool fail = false;
            for (int bit = 30; bit >= 0; bit--) if (target & (1 << bit)) {
                while(cur >= 0) {
                    if (steps[cur].se & (1 << bit)) {
                        bool ok = true;
                        for (int bigger = bit + 1; bigger <= 30; bigger++)       
                            if (steps[cur].se & (1 << bigger)) {
                                ok = false;
                                break;
                            }
                        if (ok)
                            break;
                    }
                    cur--;
                    continue;
                }
                if (cur < 0) {
                    fail = true;
                    break;
                }
                target ^= steps[cur].se;
                cur--;
            }
            if (target != 0)
                fail = true;
            printf(fail ? "NO\n" : "YES\n");
        }
        /*printf("q = %d\n", q);
        for (pii p : steps)
            printf("step %d %d\n", p.fi, p.se);*/
    }
}

