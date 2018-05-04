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

const int maxc = 1005;
const int mod = 1e9 + 7;

i64 dp[maxc][maxc];
int cnt[2][maxc];
int n, m, c;
i64 spheres[maxc];

inline void upd(i64 & x, i64 y)
{
    x = (x + y) % mod;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &c);
    forn(j, n)
    {
        int x;
        scanf("%d", &x);
        cnt[0][x]++;
    }
    forn(j, m)
    {
        int x;
        scanf("%d", &x);
        cnt[1][x]++;
    }
    fore(j, 1, c)
    {
        spheres[j] = (i64)cnt[0][j] * cnt[1][j];
//        printf("spheres[%d] = %lld\n", j, spheres[j]);
    }
    dp[0][0] = 1;
    forn(got, c + 1)
        forn(last, c) if (dp[got][last] != 0)
        {
            //printf("dp[%d][%d] = %lld\n", got, last, dp[got][last]);
            upd(dp[got + 1][last + 1], (i64)dp[got][last] * spheres[last + 1]);
            upd(dp[got][last + 1], dp[got][last]);
        }
    fore(j, 2, c + 1)
    {
        //printf("final dp[%d][c] = %lld\n", j, dp[j][c]);
        cout << dp[j][c] << " ";
    }
}

