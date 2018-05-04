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

const int mod = 1e9+7;
const int maxn = 2005;
const int X = 0;
const int Y = 1;
const int Z = 2;
int dp[maxn][maxn][3][3];

bool is_pair(int first, int third) {
    return (first == X && third == Z) || (first == Z && third == X); 
}

void upd(int & x, int y) {
    x = (x + y) % mod;
}

int mult(int x) {
    return x == Y ? 24 : 1;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, K;
    scanf("%d%d", &n, &K);
    fore(first, 0, 2)
        fore(second, 0, 2)
            fore(third, 0, 2) {
                int c = is_pair(first, third);
                upd(dp[3][c][second][third], mult(first) * mult(second) * mult(third));
            }
    fore(pos, 3, n)
        fore(k, 0, pos)
            fore(second, 0, 2)
                fore(third, 0, 2) if (dp[pos][k][second][third] > 0) {
                    fore(fourth, 0, 2) {
                        int c = is_pair(second, fourth);
                        upd(dp[pos + 1][k + c][third][fourth],
                                (i64)dp[pos][k][second][third] * mult(fourth) % mod);
                    }
                }
    int ans = 0;
    fore(second, 0, 2)
        fore(third, 0, 2)
            upd(ans, dp[n][K][second][third]);
    printf("%d", ans);
}

