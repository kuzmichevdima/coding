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

const int maxn = 105;

int a[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    forn(j, k)
        scanf("%d", &a[j]);
    int ans = 0;
    forn(i, n) {
        forn(j, m) {
            int x;
            scanf("%d", &x);
            forn(pos, k)
                if (a[pos] == x) {
                    ans += pos + 1;
                    for (int p = pos; p >= 1; p--)
                        a[p] = a[p - 1];
                    a[0] = x;
                    break;
                }
        }
    }
    printf("%d\n", ans);
}
