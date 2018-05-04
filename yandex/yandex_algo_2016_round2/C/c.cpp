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

int a[10];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    forn(j, n) {
        scanf("%d", &a[j]);
    }
    int ans = 0;
    while(true) {
        int maxx = 0;
        forn(j, n)
            maxx = max(maxx, a[j]);
        if (maxx <= 1) {
            forn(j, n)
                ans += a[j];
            break;
        }
        pii best = mp(-1, -1);
        //printf("bound = %d\n", bound);
        forn(q, n) if (a[q] > 1) {
            int cnt = 0;
            forn(j, n)
                cnt += a[j] % a[q];
            pii nnew = mp(cnt, -a[q]);
            if (best.fi == -1 || best > nnew)
                best = nnew;
        }
        ans += best.fi;
//        printf("chosen %d %d\n", best.fi, best.se);
        forn(j, n)
            a[j] = (a[j] - a[j] % (-best.se)) / (-best.se);
    }
    printf("%d\n", ans);
}
