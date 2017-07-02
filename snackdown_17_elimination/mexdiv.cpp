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

const int maxn = 5e5 + 5;
const int mod = 1e9+7;

int dp[maxn];
int pref[maxn];
int last[maxn];
int a[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    k = min(k, n);
    int start = 0;
    int covered = 0;
    fore(j, 0, k)
        last[j] = -1;
    dp[0] = pref[0] = 1;
    forn(i, n) {
        scanf("%d", &a[i]);
        if (a[i] <= k) {
            if (last[a[i]] == -1)
                covered++;
            last[a[i]] = i;
        }
        //printf("%d covered = %d start = %d last[0] = %d", a[i], covered, start, last[0]);
        fflush(stdout);
        if (covered == k + 1) {
            while(true) {
                // printf("start = %d\n", start);
                if (a[start] <= k && last[a[start]] == start) {
                    last[a[start]] = -1;
                    covered--;
                    start++;
                    break;
                }
                start++;
            }
        }
        dp[i + 1] = (pref[i] - (start == 0 ? 0 : pref[start - 1]) + mod) % mod;
        pref[i + 1] = (pref[i] + dp[i + 1]) % mod;
    }
    printf("%d", dp[n]);
}

