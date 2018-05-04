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

const int maxn = 2005;
const int maxl = 2e6;
const i64 inf = 1e18;

pii p[maxn];
int L[maxn];
int C[maxn];
i64 dp[maxl + 5];

i64 sqr(int x) {
    return (i64)x * x;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n, m;
        scanf("%d", &n);
        forn(i, n)
            scanf("%d%d", &p[i].fi, &p[i].se);
        scanf("%d", &m);
        forn(j, m) {
            scanf("%d%d", &L[j], &C[j]);
        }
        dp[0] = 0;
        fore(l, 1, maxl) {
            dp[l] = inf;
            forn(last, m) {
                int tmp = max(0, l - L[last]);
                dp[l] = min(dp[l], dp[tmp] + C[last]);
            }
        }
        //for (int l = maxl - 1; l >= 0; l--)
        //    dp[l] = min(dp[l], dp[l + 1]);
        p[n] = p[0];
        i64 ans = 0;
        forn(i, n) {
            i64 sqrlen = sqr(p[i].fi - p[i + 1].fi) + sqr(p[i].se - p[i + 1].se);
            int start = 0;
            int finish = maxl;
            while(start < finish) {
                int middle = (start + finish) / 2;
                if ((i64)middle * middle >= sqrlen)
                    finish = middle;
                else start = middle + 1;
            }
            int l = start;
            ans += dp[l];
            /*int tmp = l / L[0];
            if (l % L[0] != 0)
                tmp++;
            ans += (i64)C[0] * tmp;*/
        }
        cout << ans << endl;
    }
}
