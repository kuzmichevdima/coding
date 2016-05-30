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

const int maxn = 2e5+5;

int x[maxn];
int t[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    fore(j, 1, n)
        scanf("%d%d", &x[j], &t[j]);
    x[n + 1] = 0;
    int ans = 0;
    fore(rpos, 1, n + 1) if (x[rpos] >= 0) {
        int R = x[rpos];
        int cur = 0; 
        fore(chosen, 1, n) {
            if (x[chosen] < 0) {
                if (x[chosen] - R - R > -t[chosen])
                    cur++;
            } else if (R >= x[chosen]) {
                if (t[chosen] > x[chosen])
                    cur++;
            }
        }
 //       printf("R = %d cur = %d\n", R, cur);
        if (cur % 2 == 0)
            cur--;
        ans = max(ans, cur);
    }

    fore(lpos, 1, n + 1) if (x[lpos] <= 0) {
        int L = x[lpos];
        int cur = 0;
        fore(chosen, 1, n) {
            if (x[chosen] > 0) {
                if (x[chosen] - L - L < t[chosen])
                    cur++;
            } else if (L <= x[chosen]) {
                if (t[chosen] > -x[chosen])
                    cur++;
            }
        }
   //     printf("L = %d cur = %d\n", L, cur);
        if (cur % 2 == 0)
            cur--;
        ans = max(ans, cur);
    }

    printf("%d\n", ans);
}

