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

const int maxn = 2e5+5;

bool dp[maxn][8][8];
int a[maxn];

inline void upd(int pos, int i, int j, int deltai, int deltaj)
{
    int newi = i + deltai;
    int newj = j + deltaj;
    if (a[pos] != newi && a[pos] != newj)
        return;
    dp[pos][newi][newj] = true;
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
    forn(j, n)
    {
        scanf("%d", &a[j]);
        assert(a[j] >= 1 && a[j] <= 7);
    }
    fore(i, 1, 7)
        dp[0][a[0]][i] = dp[0][i][a[0]] = true;
    forn(pos, n - 1)
        fore(i, 1, 7)
            fore(j, 1, 7) if (dp[pos][i][j])
            {
                if (i > 1)
                    upd(pos + 1, i, j, -1, 0);
                if (i < 7)
                    upd(pos + 1, i, j, +1, 0);
                if (j > 1)
                    upd(pos + 1, i, j, 0, -1);
                if (j < 7)
                    upd(pos + 1, i, j, 0, +1);
                upd(pos + 1, i, j, 0, 0);
            }
    fore(i, 1, 7)
        fore(j, 1, 7)
            if (dp[n - 1][i][j])
            {
                vector <pii> ans;
                int curi = i;
                int curj = j;
                for (int p = n - 1; p >= 0; p--)
                {
                    ans.pb(mp(curi, curj));
                    if (p != 0)
                    {
                        if (dp[p - 1][curi - 1][curj])
                            curi--;
                        else if (dp[p - 1][curi + 1][curj])
                            curi++;
                        else if (dp[p - 1][curi][curj - 1])
                            curj--;
                        else if (dp[p - 1][curi][curj + 1])
                            curj++;
                    }
                }
                printf("YES\n");
                for (int k = n - 1; k >= 0; k--)
                    printf("%d %d\n", ans[k].fi, ans[k].se);
                exit(0);
            }
    printf("NO\n");
}

