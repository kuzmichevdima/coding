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

const int MOD = 1e9+7;
const int maxn = 1005;

int n;
int c[maxn];
int C[maxn][maxn];
int dp[maxn][maxn];
int pref[maxn];

void add(int & x, int y)
{
    x = (x + y) % MOD;
}

void precalc()
{
   C[0][0] = C[1][0] = C[1][1] = 1;
   fore(i, 2, n)
    {
        C[i][0] = 1;
        fore(j, 1, i)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
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
    int k;
    scanf("%d", &k);
    forn(j, k)
    {
        scanf("%d", &c[j]);
        if (j == 0)
            pref[j] = c[j];
        else pref[j] = pref[j - 1] + c[j];
        n += c[j];
    }
    precalc();
    dp[1][0] = 1;
    fore(pos, 1, n)
        forn(cur, k) if (dp[pos][cur] != 0)
        {
       //     printf("dp[%d][%d] = %d\n", pos, cur, dp[pos][cur]);
            add(dp[pos + 1][cur], dp[pos][cur]);
            int N = pos - 1 - (cur == 0 ? 0 : pref[cur - 1]);
            int K = c[cur] - 1;
            if (N >= K)
            {
                int CC = C[N][K];
                add(dp[pos + 1][cur + 1], (i64)dp[pos][cur] * CC % MOD);
            }
        }
    printf("%d", dp[n + 1][k]);
}
