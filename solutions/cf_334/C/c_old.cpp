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

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    //scanf("%d%d", &n, &k);
    //forn(j, n)
    //    scanf("%d", &a[j]);
    fore(k, 1, 10)
    {
        printf("k = %d\n", k);
        vector <int> dp(100);
        dp[1] = 1;

        fore(j, 2, 40)
        {
            if (j % 2 == 1)
            {
                dp[j] = (dp[j - 1] == 0 ? 1 : 0);   
            }
            else
            {
                int split = (k % 2 == 1 ? dp[j / 2] : 0);
                fore(h, 0, 2)
                    if (split != h && h != dp[j - 1])
                    {
                        dp[j] = h;
                        break;
                    }
            }
            printf("dp[%d] = %d\n", j, dp[j]);
        }
    }
}
