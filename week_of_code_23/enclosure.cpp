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

#define ld long double

const ld PI = 3.141592653589793238462643383;

const int maxn = 1e4+5;
const int iter_count = 300;

ld a[maxn];
ld cos_a[maxn];
int n;

typedef pair <ld, ld> mytype;
mytype ans[maxn];

ld get(ld r) {
    ld res = 0;
    forn(j, n) {
        cos_a[j] = -a[j] * a[j] / (2 * r * r) + 1;
        res += acos(cos_a[j]);
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    ld s = 0;
    forn(j, n) {
        double x;
        scanf("%lf", &x);
        a[j] = x;
        s = max(s, a[j] / 2);
    }
    //ld tmp = get(sqrt(5) / 2);
//    printf("%.10lf tmp = %.10lf\n", sqrt(5) / 2, (double)tmp);
    ld f = 1e18;
    forn(iter, iter_count) {
        ld m = (s + f) / 2;
        ld g = get(m);
        if (g < 2 * PI)
            f = m;
        else s = m;
    }
    get(s);
    ld R = s;
    //printf("%.10lf\n", (double)s);
    ld x = sqrt(R * R - a[0] * a[0] / 4);
    mytype center = mp(x, a[0] / 2);
    mytype cur = mp(-x, -a[0] / 2);
    ans[0] = mp(0, 0);
    fore(j, 0, n - 2) {
        ld sin_a = sqrt(1 - cos_a[j] * cos_a[j]);
//        printf("cos = %.10lf sin = %.10lf\n", (double)cos_a[j], (double)sin_a);
  //      printf("cur = %.10lf %.10lf\n", (double)cur.fi, (double)cur.se);
        mytype nnew = mp(cos_a[j] * cur.fi + sin_a * cur.se, -sin_a * cur.fi + cos_a[j] * cur.se);
    //    printf("nnew = %.10lf %.10lf\n", (double)nnew.fi, (double)nnew.se);
        ans[j + 1] = mp(center.fi + nnew.fi, center.se + nnew.se);
        cur = nnew;
    }
    forn(j, n) {
        printf("%.10lf\n%.10lf\n\n", (double)ans[j].fi, (double)ans[j].se);
    }
}

