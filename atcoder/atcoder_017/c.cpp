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

const int maxn = 205;
const int inf = 2e9;

int prec[maxn][maxn];
int dp[maxn];
int a[maxn];
int b[maxn];

inline void upd(int & x, int y) {
    x = min(x, y);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(i, n) {
        scanf("%d", &a[i]);
    }
    forn(j, m) {
        int pos, val;
        scanf("%d%d", &pos, &val);
        a[pos - 1] = val;
        forn(j, n) {
            b[j] = a[j];
        }
        sort(b, b + n);
        forn(j, n)
            printf("%d ", b[j]);
        printf("\n");
        dp[0] = 0;
        fore(j, 1, n)
            dp[j] = inf;
        fore(next, 1, n) {
            fore(i, 0, next - 1)
                prec[next][i] = (i == 0 ? 0 : prec[next][i - 1]) + abs(b[i] - next);
        }
        fore(cur, 0, n - 1) {
            fore(next, cur + 1, n) {
                int to_add = prec[next][next - 1] - (cur == 0 ? 0 : prec[next][cur - 1]);
                upd(dp[next], dp[cur] + to_add);
            }
        }
        printf("%d\n", dp[n]);
    }
}

