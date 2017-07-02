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
const int inf = 1e9;
int cnt[5];
vi v;
int dp[maxn][maxn][maxn][5];

inline void upd(int & x, int y) {
    x = max(x, y);
}


int main() {
    int tests;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        cerr << "test " << test << endl;
        int n, p;
        scanf("%d%d", &n, &p);
        memset(cnt, 0, sizeof(cnt));
        forn(j, n) {
            int x;
            scanf("%d", &x);
            cnt[x % p]++;
        }
        fore(one, 0, cnt[1])
            fore(two, 0, cnt[2])
                fore(three, 0, cnt[3])
                    fore(cur, 0, p - 1)
                        dp[one][two][three][cur] = -inf;
        dp[0][0][0][0] = 0;
        fore(one, 0, cnt[1])
            fore(two, 0, cnt[2])
                fore(three, 0, cnt[3])
                    fore(cur, 0, p - 1) if (dp[one][two][three][cur] != -inf) {
                        int t = dp[one][two][three][cur] + (cur == 0);
                        if (one != cnt[1])
                            upd(dp[one + 1][two][three][(cur + 1) % p], t);
                        if (two != cnt[2])
                            upd(dp[one][two + 1][three][(cur + 2) % p], t);
                        if (three != cnt[3])
                            upd(dp[one][two][three + 1][(cur + 3) % p], t);
                    }
        int ans = 0;
        fore(cur, 0, p - 1)
            ans = max(ans, dp[cnt[1]][cnt[2]][cnt[3]][cur]);
        assert(ans != -inf);
        ans += cnt[0];
        printf("Case #%d: %d\n", test, ans);
    }
}

