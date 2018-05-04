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

const int maxn = 1e5+5;
int n;
int arr[maxn];
int dp[maxn][45];

inline void upd(int & x, int y) {
    x = max(x, y);
}

int solve(int a, int b, int w, int h) {
    memset(dp, 0, sizeof(dp));
    dp[w][0] = h;
    fore(first, 1, a)
        forn(idx, n) if (dp[first][idx] != 0) {
            //cerr << first << " " << idx << " " << dp[first][idx] << endl;
            i64 new_first = (i64)first * arr[idx];
            if (new_first > a)
                new_first = a;
            upd(dp[new_first][idx + 1], dp[first][idx]);
            i64 new_second = (i64)dp[first][idx] * arr[idx];
            if (new_second > b)
                new_second = b;
            upd(dp[first][idx + 1], new_second);
        }
    forn(idx, n + 1)
        if (dp[a][idx] >= b)
            return idx;
    return -1;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int a, b, w, h;
    scanf("%d%d%d%d%d", &a, &b, &w, &h, &n);
    forn(j, n)
        scanf("%d", &arr[j]);
    sort(arr, arr + n);
    reverse(arr, arr + n);
    if (n > 40)
        n = 40;
    int ans = solve(a, b, w, h);
    swap(w, h);
    int ans2 = solve(a, b, w, h);
    if (ans == -1 || (ans2 != -1 && ans2 < ans))
        ans = ans2;
    printf("%d", ans);
}

