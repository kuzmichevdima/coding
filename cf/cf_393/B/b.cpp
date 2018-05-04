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

const int maxn = 1e5+5;

int t[maxn];
int dp[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    forn(j, n) {
        scanf("%d", &t[j]);
        dp[j] = (j == 0 ? 0 : dp[j - 1]) + 20;
        int nxt = upper_bound(t, t + j + 1, t[j] - 90) - t;
        dp[j] = min(dp[j], (nxt == 0 ? 0 : dp[nxt - 1]) + 50);

        nxt = upper_bound(t, t + j + 1, t[j] - 1440) - t;
        dp[j] = min(dp[j], (nxt == 0 ? 0 : dp[nxt - 1]) + 120);
        printf("%d\n", dp[j] - (j == 0 ? 0 : dp[j - 1])); 
    }
}
