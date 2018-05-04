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

int ans;

void upd(int& x, int y) {
    x = max(x, y);
    ans = max(ans, y);
}

const int maxn = 305;

int dp[maxn][maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int k;
    string s;
    cin >> s >> k;
    int n = s.length();
    fore(l1, 0, n)
        fore(l2, 0, n - l1 - 1)
            fore(changes, 0, k) {
                //printf("dp = %d l1 = %d l2 = %d changes = %d\n", dp[l1][l2][changes], l1, l2, changes);
                upd(dp[l1 + 1][l2][changes], dp[l1][l2][changes]);
                upd(dp[l1][l2 + 1][changes], dp[l1][l2][changes]);
                int addit = l1 == n - l2 - 1 ? 1 : 2;
                if (s[l1] == s[n - l2 - 1]) {
                    upd(dp[l1 + 1][l2 + 1][changes], dp[l1][l2][changes] + addit);
                } else if (changes < k) {
                    upd(dp[l1 + 1][l2 + 1][changes + 1], dp[l1][l2][changes] + addit);
                }
            }
    printf("%d", ans);
}

