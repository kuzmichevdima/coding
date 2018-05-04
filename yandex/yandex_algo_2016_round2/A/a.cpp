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

map <string, int> M;
int cost[maxn][maxn];
int dp[maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tmp1, tmp2;
    int m;
    scanf("%d%d", &tmp1, &m);
    string s;
    cin >> s;
    int n = s.length();
    forn(j, m) {
        int c;
        scanf("%d%d", &tmp2, &c);
        string t;
        cin >> t;
        forn(i, t.length())
            fore(j, 1, (int)t.length() - i) {
                string part = t.substr(i, j);
                if (M.find(part) == M.end())
                    M[part] = c * j;
                else M[part] = min(M[part], c * j);
            }
    }
    forn(i, n)
        fore(j, i, n - 1) {
            string part = s.substr(i, j - i + 1);
            cost[i][j] = M.find(part) == M.end() ? inf : M[part];
        }
    fore(len, 1, s.length())
        forn(i, s.length() - len + 1) {
            int j = i + len - 1;
            dp[i][j] = inf;
            fore(j1, i, j) {
                int nnew = cost[i][j1] + (j1 == j ? 0 : dp[j1 + 1][j]);
                dp[i][j] = min(dp[i][j], nnew);
            }
            fore(i1, i, j) {
                int nnew = cost[i1][j] + (i1 == i ? 0 : dp[i][i1 - 1]);
                dp[i][j] = min(dp[i][j], nnew);
            }
        }
    if (dp[0][n - 1] == inf)
        cout << -1;
    else printf("%d", dp[0][n - 1]);
}
