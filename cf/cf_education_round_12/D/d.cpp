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

const int maxn = 2e6;
bool mark[maxn + 5];
int a[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    fore(i, 2, maxn) if (!mark[i]) {
        for (int j = 2 * i; j <= maxn;j += i)
            mark[j] = true;
    }
    int n;
    scanf("%d", &n);
    int cnt1 = 0;
    forn(i, n) {
        scanf("%d", &a[i]);
        if (a[i] == 1)
            cnt1++;
    }
    int best = 0;
    pii best0, best1;
    forn(i, n)
        fore(j, i + 1, n - 1) if (!mark[a[i] + a[j]] && a[i] != a[j]) {
            int t1 = (a[i] == 1 ? cnt1 : 1);
            int t2 = (a[j] == 1 ? cnt1 : 1);
            int nnew = t1 + t2;
            if (nnew > best) {
                best = nnew;
                best0 = mp(a[i], t1);
                best1 = mp(a[j], t2);
            }
        }
    int best_solo, solo;
    if (cnt1 > 0) {
        best_solo = 1;
        solo = cnt1;
    }
    else {
        best_solo = a[0];
        solo = 1;
    }
    if (best > solo) {
        printf("%d\n", best);
        forn(j, best0.se)
            printf("%d ", best0.fi);
        forn(j, best1.se)
            printf("%d ", best1.fi);
    } else {
        printf("%d\n", solo);
        forn(j, solo)
            printf("%d ", best_solo);
    }
}
