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

i64 dp[maxn];
int dx, dy, n;
pii order[maxn];
int points[maxn];
int x[maxn];
int y[maxn];
int h[maxn];

class cmp {
    
    bool operator()(int x1, int y1) {
    return x[x1] < y[y1];
    }
};

set <int, cmp> S;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &dx, &dy);
    forn(i, n) {
        scanf("%d%d%d%d", &x[i], &y[i], &h[i], &points[i]);
        order[i] = mp(h[i], i);
    }
    sort(order, order + n);
    forn(i, n) {
        int numi = order[i].se;
        dp[numi] = points[numi];
        i64 maxx = 0;
        auto lowerx = S.lower_bound(numi);
        auto upperx = S.upper_bound(numi);
        for (auto iter = lowerx; iter != upperx; ++iter) {
                int numj = (*iter);
                if (h[numj] < h[numi] && abs(y[numj] - y[numi]) <= dy)
                    maxx = max(maxx, dp[numj]);
        }
        dp[numi] += maxx;
        S.insert(numi);
    }
    i64 ans = 0;
    forn(i, n)
        ans = max(ans, dp[i]);
    cout << ans;
}
