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

const i64 inf = 1e18+5;

const int maxn = 55;

i64 dp[maxn];
int n;
i64 k;


int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    cin >> n >> k;
    dp[1] = dp[0] = 1;
    fore(j, 2, n)
    {
        dp[j] = dp[j - 1] + dp[j - 2];
        if (dp[j] > inf)
            dp[j] = inf;
    }
    int L = n;
    while(L > 0)
    {
        if (dp[L - 1] >= k)
        {
            printf("%d ", n - L + 1);
            L--;
        }
        else
        {
            k -= dp[L - 1];
            printf("%d %d ", n - L + 2, n - L + 1);
            L -= 2;
        }
    }


}
