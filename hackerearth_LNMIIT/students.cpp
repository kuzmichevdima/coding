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

const int maxpr = 1 << 16;
const int inf = 2e9;
const int maxn = 20;
int dp[maxpr + 5];
int a[maxn][maxn];
vector< pii> edges[maxn];
int init[maxn];
int fr[maxpr];

inline void upd(int prof, int val, int chosen) {
    if (val < dp[prof]) {
        dp[prof] = val;
        fr[prof] = chosen;
    }
}

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
    forn(i, n)
        forn(j, n)
            scanf("%d", &a[i][j]);
    forn(i, n)
        scanf("%d", &init[i]);
    forn(i, n) {
        int k;
        scanf("%d", &k);
        forn(j, k) {
            int num, delta;
            scanf("%d%d", &num, &delta);
            num--;
            edges[num].pb(mp(i, delta));
        }
    }
    fore(pr, 1, (1 << n) - 1)
        dp[pr] = inf;
    dp[0] = 0;
    fore(prof, 0, (1 << n) - 2) if (dp[prof] != inf) {
        int cur = 0;
        forn(i, n)
            if (prof & (1 << i))
                cur++;
        forn(chosen, n) {
            if (!a[cur][chosen])
                continue;
            int pay = init[chosen];
            for (pii p : edges[chosen])
                if (prof & (1 << p.fi))
                    pay -= p.se;
            upd(prof | (1 << chosen), dp[prof] + pay, chosen);
        }
    }
    printf("%d\n", dp[(1 << n) - 1]);
    int prof = (1 << n) - 1;
    vi ans;
    forn(j, n) {
        ans.pb(fr[prof]);
        prof = prof - (1 << fr[prof]);
    }
    for (int j = (int)ans.size() - 1; j >= 0; j--)
        printf("%d ", ans[j] + 1);
}

