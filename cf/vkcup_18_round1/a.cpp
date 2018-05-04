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
    int x2;
    scanf("%d", &x2);
    vi prec(x2 + 1);
    int maxx = 0;
    fore(i, 2, x2)
        if (prec[i] == 0) {
            for (int j = 2 * i; j <= x2; j += i)
                prec[j] = i;
            if (2 * i <= 1000000)
                maxx = i;
        }
    printf("%d\n", maxx * 2);
    int lower = x2 - prec[x2] + 1;
    printf("prec[x2] = %d\n", prec[x2]);
    int ans = x2;
    fore(x1, lower, x2) {
        //printf("x1 = %d prec = %d\n", x1, prec[x1]);
        if (prec[x1])
            ans = min(ans, x1 - prec[x1] + 1);
    }
    printf("%d", ans);
}

