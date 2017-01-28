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

#define double long double

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

struct Line {
    i64 a, b, c;
    Line (pii first, pii second) {
        a = second.se - first.se;
        b = first.fi - second.fi;
        c = -a * first.fi - b * first.se;
    }
};

const int maxn = 55;

double sqr(double x) {
    return x * x;
}

pii p[maxn];
int R;

inline int get(vector <pii> & v) {
    vi ux, uy;
    for (pii p : v) {
        ux.pb(p.fi);
        uy.pb(p.se);
    }
    sort(ux.begin(), ux.end());
    sort(uy.begin(), uy.end());
    ux.resize(unique(ux.begin(), ux.end()) - ux.begin());
    uy.resize(unique(uy.begin(), uy.end()) - uy.begin());
    int result = 0;
    for (int x : ux)
        for (int y : uy) {
            int nnew = 0;
            for (pii p : v)
                if (p.fi >= x && p.fi <= x + R && p.se >= y && p.se <= y + R)
                    nnew++;
            result = max(result, nnew);
        }
    return result;
}

int main() {
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        fprintf(stderr, "test %d\n", test);
        int n;
        scanf("%d%d", &n, &R);
        forn(j, n)
            scanf("%d%d", &p[j].fi, &p[j].se);
        int ans = 0;
        forn(i, n)
            fore(j, i + 1, n - 1)
                fore(k, j + 1, n - 1) {
                    Line l1(p[i], p[j]);
                    //printf("(%d %d) (%d %d) %d %d %d\n", p[i].fi, p[i].se, p[j].fi, p[j].se, l1.a, l1.b, l1.c);
                    Line l2(p[j], p[k]);
                    if (l1.a * l2.b == l1.b * l2.a) {
 //                       printf("%d %d %d\n", i, j, k);
                        continue;
                    }
                    double cy = (double)(l2.c * l1.a - l2.a * l1.c) / (l1.b * l2.a - l2.b * l1.a);
                    double cx = (double)(l2.c * l1.b - l2.b * l1.c) / (l1.a * l2.b - l2.a * l1.b);
                    double r2 = sqr(cx - p[i].fi) + sqr(cy - p[i].se);
                    vector <pii> inner, outer;
                    forn(h, n)
                        if (sqr(cx - p[h].fi) + sqr(cy - p[h].se) <= r2)
                            inner.pb(p[h]);
                        else outer.pb(p[h]);
                    int nnew = get(inner) + get(outer);
                    ans = max(ans, nnew);
                }
        forn(i, n) {
            vector <pii> outer;
            forn(j, n) if (i != j)
                outer.pb(p[j]);
            ans = max(ans, 1 + get(outer));
        }
        forn(i, n)
            forn(j, n) if (i != j) {
                    double cy = p[j].fi;
                    double cx = p[j].se;
                    double r2 = sqr(cx - p[i].fi) + sqr(cy - p[i].se);
                    vector <pii> inner, outer;
                    forn(h, n)
                        if (sqr(cx - p[h].fi) + sqr(cy - p[h].se) <= r2)
                            inner.pb(p[h]);
                        else outer.pb(p[h]);
                    int nnew = get(inner) + get(outer);
                    ans = max(ans, nnew);

            }
        printf("Case #%d: %d\n", test + 1, ans);
    }
}
