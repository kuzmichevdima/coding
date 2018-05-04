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

const int maxlen = 1005;
const int maxn = 1e5 + 5;

int dp[maxlen][maxlen];
int a[maxn];
vi edges[maxn];
int cnt = 0;
int color[maxn];

void dfs(int v) {
    color[v] = cnt;
    for (int u : edges[v]) {
        if (color[u] == 0)
            dfs(u);
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int letters, rules, len;
    scanf("%d%d%d", &letters, &rules, &len);
    forn(i, rules) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    forn(j, len) {
        scanf("%d", &a[j]);
    }
    fore(i, 1, letters) {
        if (color[i] == 0) {
            cnt++;
            dfs(i);
        }
    }
    forn(i, len)
        dp[i][i] = 1;
    fore(L, 2, len) {
        fore(start, 0, len - L) {
            int finish = start + L - 1;
            dp[start][finish] = max(dp[start + 1][finish], dp[start][finish - 1]);
            if (color[a[start]] == color[a[finish]])
                dp[start][finish] = max(dp[start][finish], 2 + dp[start + 1][finish - 1]);
        }
    }
    printf("%d", dp[0][len - 1]);
}

