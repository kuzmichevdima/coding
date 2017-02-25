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

int f[maxn];
int h[maxn];
int g[maxn];

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
    vi vals(n);
    fore(j, 1, n) {
        scanf("%d", &f[j]);
        vals[j - 1] = f[j];
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    int m = vals.size();
    forn(pos, m) {
        h[pos + 1] = vals[pos];
        //printf("h[%d] = %d\n", pos + 1, h[pos + 1]);
    }
    fore(x, 1, n)
        g[x] = lower_bound(vals.begin(), vals.end(), f[x]) - vals.begin() + 1;
    fore(x, 1, m) {
        if (g[h[x]] != x) {
            printf("-1");
            exit(0);
        }
    }
    printf("%d\n", m);
    fore(x, 1, n)
        printf("%d ", g[x]);
    printf("\n");
    fore(x, 1, m)
        printf("%d ", h[x]);


}
