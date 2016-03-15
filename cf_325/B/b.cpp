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

const int maxn = 105;

bool banned[maxn][3];
bool dp[maxn][3];

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
    forn(test, tests)
    {
        int useless, W, start_pos = 0;
        scanf("%d%d", &W, &useless);
        memset(banned, false, sizeof(banned));
        forn(row, 3)
        {
            string s;
            cin >> s;
            forn(j, W)
            {
                if (s[j] == 's')
                {
                    start_pos = row;
                    continue;
                }
                if (s[j] != '.')
                {
                    int t = 1;
                    int cur = j;
                    while(cur >= 0)
                    {
                        if (t == cur)
                        {
                            banned[t][row] = banned[t - 1][row] = true;
                        }
                        cur--;
                        if (t == cur)
                            banned[t][row] = true;
                        cur--;
                        if (t == cur)
                            banned[t][row] = true;
                        t++;
                    }
                }
            }
        }
/*        forn(row, 3)
        {
            forn(t, W)
                printf("%d", banned[t][row]);
            printf("\n");
        }*/
//        printf("start_pos = %d\n", start_pos);
        if (banned[0][start_pos])
        {
            printf("NO\n");
            continue;
        }
        memset(dp, false, sizeof(dp));
        dp[0][start_pos] = true;
        forn(t, W)
            forn(pos, 3) if (dp[t][pos])// && !banned[t + 1][pos])
            {
                if (pos > 0 && !banned[t + 1][pos - 1])
                    dp[t + 1][pos - 1] = true;
                if (pos < 2 && !banned[t + 1][pos + 1])
                    dp[t + 1][pos + 1] = true;
                if (!banned[t + 1][pos])
                    dp[t + 1][pos] = true;
            }
        bool found = false;
        forn(pos, 3)
            if (dp[W - 1][pos])
                found = true;
        if (found)
            printf("YES\n");
        else printf("NO\n");
    }
}
