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

const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};
const int maxn = 1e5+5;
pii a[maxn];

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
        int n, k;
        scanf("%d%d", &n, &k);
        set <pii> S;
        pii top = mp(-1e9, -1e9);
        forn(i, n) {
            scanf("%d%d", &a[i].fi, &a[i].se);
            S.insert(a[i]);
            if (a[i].se > top.se)
                top = a[i];
        }
        set <pii> order;
        order.insert(top);
        S.erase(top);
        printf("U %d\n", top.se + 1);
        forn(i, n)
            printf("%d %d\n", a[i].fi, a[i].se);
        forn(iter, k - n) {
            pii cur = *order.begin();
            order.erase(order.begin());
            printf("%d %d\n", cur.fi, 2 * top.se - cur.se + 1);
            forn(move, 4) {
                pii nnew = mp(cur.fi + dx[move], cur.se + dy[move]);
                if (S.find(nnew) != S.end()) {
                    order.insert(nnew);
                    S.erase(nnew);
                }
            }
        }
    }
}

