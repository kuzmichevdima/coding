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

int a[1005];
vi e[1005];
int maxx;

void go(int v, int ban, int d) {
//    printf("v = %d ban = %d d = %d\n", v, ban, d);
    maxx = max(maxx, d);
    for (int u : e[v]) if (u != ban) {
        go(u, ban, d + 1);
    }
}

int main() {
#ifdef LOCAL
//    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        int n;
        scanf("%d", &n);
        fore(j, 1, n)
            e[j].clear();
        fore(j, 1, n)
         {
            scanf("%d", &a[j]);
            e[a[j]].pb(j);
            }
        int max_cycle = 0;
        fore(j, 1, n) if (a[a[j]] != j) {
            int cur = j;
            int len = 1;
            set <int> vis;
            while(true) {
                cur = a[cur];
                if (cur == j) {
                    max_cycle = max(max_cycle, len);
                    break;
                }
                if (vis.find(cur) != vis.end()) {
                    break;
                }
                vis.insert(cur);
                len++;
            }
        }
        //printf("cycle %d\n", max_cycle);
        int sum = 0;
        fore(j, 1, n) if (a[a[j]] == j && a[j] > j) {
            maxx = 0;
            go(j, a[j], 0);
            sum += maxx;
            maxx = 0;
            go(a[j], j, 0);
            sum += 2 + maxx;
        }
        int ans = max(sum, max_cycle);
        cerr << test << endl;
        printf("Case #%d: %d\n", test, ans);
        assert(ans <= n);
    }
}
