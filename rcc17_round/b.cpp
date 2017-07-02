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

const int SHIFT = 1;
const int INPUT = 0;

const i64 inf = 1e18;
const int maxn = 2005;
bool can[maxn][maxn];
i64 dp[maxn][maxn][2];

inline void upd(i64 & x, i64 y) {
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
    int n, a, b, c;
    scanf("%d%d%d%d", &n, &a, &b, &c);
    forn(j, n) {
        string str;
        cin >> str;
        for (char c : str)
            can[j][c - 'a'] = true;
    }
    string s;
    cin >> s;
    int len = s.length();
    forn(done, len + 1)
        forn(cur, n)
            forn(flag, 2)
                dp[done][cur][flag] = inf;
    dp[0][0][INPUT] = 0;
    forn(done, len)
        forn(iter, 2)
            forn(cur, n)
                forn(flag, 2)
                    if (dp[done][cur][flag] != inf) {
                        //printf("done = %d cur = %d flag = %d\n", done, cur, flag);
                        if (can[cur][s[done] - 'a'])
                            upd(dp[done + 1][cur][INPUT], dp[done][cur][flag] + c);
                        i64 tmp = dp[done][cur][flag] + (flag == INPUT ? a : b);
                        upd(dp[done][(cur + 1) % n][SHIFT], tmp);
                    }
    i64 ans = inf;
    forn(cur, n)
        forn(flag, 2)
            ans = min(ans, dp[len][cur][flag]);
    if (ans == inf)
        ans = -1;
    cout << ans;
}

