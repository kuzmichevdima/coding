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
int p[1005];

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
            scanf("%d", &a[j]);
        fore(j, 1, n)
            p[j] = j;
        int ans = 2;
        do {
            fore(j, ans + 1, n) {
                bool fail = false;
                fore(pos, 1, j) {
                    int prev = (pos == 1 ? j : pos - 1);
                    int next = (pos == j ? 1 : pos + 1);
                    if (a[p[pos]] != p[prev] && a[p[pos]] != p[next]) {
                        fail = true;
                        break;
                    }
                }
                if (!fail)
                    ans = j;
            }
        } while(next_permutation(p + 1, p + n + 1));
        printf("Case #%d: %d\n", test, ans);
    }
}
