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
    int n, w;
    scanf("%d%d", &n, &w);
    vi x(n);
    vi v(n);
    forn(i, n) {
        scanf("%d%d", &x[i], &v[i]);
    }
    vector<double> z(n);
    vector<double> q(n);
    forn(i, n) {
        z[i] = (double)x[i] / (v[i] - w);
        q[i] = (double)x[i] / (v[i] + w);
        printf("i =%d x = %d z = %.5lf q = %.5lf\n", i, x[i], z[i], q[i]);
    }
    int cnt = 0;
    forn(i, n) {
        int sgn = v[i] > 0;
        printf("i = %d sgn = %d\n", i, sgn);
        forn(j, n) if (i != j) { 
            if (x[i] >= x[j] && ((sgn && z[i] <= z[j]) || (!sgn && z[i] >= z[j])) && ((q[i] >= q[j] && sgn) || (q[i] <= q[j] && !sgn))) {
                printf("i = %d j = %d\n", i, j);
                cnt++;
            }
        }
    }
    printf("cnt = %d\n", cnt);
}

