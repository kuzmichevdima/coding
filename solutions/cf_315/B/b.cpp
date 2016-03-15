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

const int maxn = 4005;
const int MOD = 1e9+7;

int n;
int dp[maxn];
int C[maxn][maxn];
//int powers[maxn][maxn];

void precalc()
{
    C[1][0] = C[1][1] = 1;
    fore(i, 2, n)
    {
        C[i][0] = 1;
        fore(j, 1, i)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    /*fore(i, 1, n)
    {
        powers[i][0] = 1;
        fore(j, 1, n)
            powers[i][j] = (i64)powers[i][j - 1] * i % MOD;
    }*/
    dp[0] = dp[1] = 1;
    fore(i, 2, n - 1)
    {
      //  int mult = 1;
        for (int k = i; k >= 1; k--)
        {
           /* mult = (i64)mult * k % MOD;
            i64 addit = (i64)mult * powers[k][i - k] % MOD;
            dp[i] = (dp[i] + addit) % MOD;*/
            dp[i] = (dp[i] + (i64)dp[i - k] * C[i - 1][k - 1] % MOD) % MOD;
        }
    }
//    fore(i, 2, n - 1)
  //      printf("dp[%d] = %d\n", i, dp[i]);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    precalc();
    int ans = 1;
    fore(k, 1, n - 1)
    {
        ans = (ans + (i64)C[n][k] * dp[k] % MOD) % MOD;   
    }
    printf("%d", ans);
}
