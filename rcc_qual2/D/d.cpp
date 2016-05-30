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

const int maxn = 15;

int fav[3][maxn];
int num_fav[3][maxn];
int dp[1 << maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n;
        scanf("%d", &n);
        forn(i, 3)
            forn(j, n) {
                scanf("%d", &fav[i][j]);
                fav[i][j]--;
                num_fav[i][fav[i][j]] = j;
            }
        forn(prof, 1 << n) {
            int bit_cnt = 0;
            int non_zero;
            forn(j, n) if (prof & (1 << j)) {
                non_zero = j;
                bit_cnt++;
            }
            if (bit_cnt == 1) {
                dp[prof] = non_zero;
                continue;
            }
            int cur = (n - bit_cnt) % 3;

            dp[prof] = -1;
            forn(chosen, n) if (prof & (1 << chosen)) {
                int new_prof = prof ^ (1 << chosen);
                if (dp[prof] == -1 || num_fav[cur][dp[new_prof]] < num_fav[cur][dp[prof]])
                    dp[prof] = dp[new_prof];
            }
        }
        printf("%d\n", dp[(1 << n) - 1] + 1);


    }
}
