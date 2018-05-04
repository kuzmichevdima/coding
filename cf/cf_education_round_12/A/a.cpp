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

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int a, ta, b, tb, h, m;
    scanf("%d%d%d%d", &a, &ta, &b, &tb);
    scanf("%d:%d", &h, &m);
    int tstart = h * 60 + m;
    int tfinish = tstart + ta;
 //   printf("%d %d\n", tstart, tfinish);
    int ans = 0;
    for (int x1 = 5 * 60; x1 < 24 * 60; x1 += b) {
        int x2 = x1 + tb;
//        printf("x1 = %d x2 = %d\n", x1, x2);
        if (max(tstart, x1) < min(tfinish, x2))
            ans++;
    }
    cout << ans;

}
