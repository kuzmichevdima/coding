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

const int maxn = 1005;

bool dp[maxn][maxn];

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
        string S, T;
        cin >> S >> T;
        memset(dp, false, sizeof(dp));
        dp[0][0] = true;
        forn(i, S.length())
            forn(j, T.length() + 1) if (dp[i][j]) {
                if (S[i] >= 'a' && S[i] <= 'z')
                    dp[i + 1][j] = true;
                if (j != (int)T.length() && (S[i] == T[j] || S[i] - 'a' + 'A' == T[j]))
                    dp[i + 1][j + 1] = true;
            }
        cout << (dp[S.length()][T.length()] ? "YES" : "NO") << endl;

    }
}
