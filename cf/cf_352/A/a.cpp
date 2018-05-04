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
#define ld long double

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

struct Point {
    i64 x, y;
    ld dist(Point an) {
        return sqrt((x - an.x) * (x - an.x) + (y - an.y) * (y - an.y));
    }
};

const int maxn = 1e5+5;

Point p[maxn];
Point A, B, U;
int n;


int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    cin >> A.x >> A.y >> B.x >> B.y >> U.x >> U.y >> n;
    ld sum = 0.0;
    forn(j, n) {
        cin >> p[j].x >> p[j].y;   
        sum += 2 * p[j].dist(U);
    }
    //cout << sum << endl;
 
    pair <ld, int> min1 = mp(0.0, -1);
    pair <ld, int> min2 = mp(0.0, -1);
    ld best;
    forn(j, n) {
        ld val = B.dist(p[j]) - U.dist(p[j]);
        if (val < min1.fi) {
            min2 = min1;
            min1 = mp(val, j);
        } else if (val < min2.fi) {
            min2 = mp(val, j);
        }
        if (j == 0 || sum + val < best) {
            best = sum + val;
        }
    }

    forn(j, n) {
        ld nnew = sum;
        nnew = nnew - U.dist(p[j]) + A.dist(p[j]);
        if (j == min1.se)
            nnew = nnew + min2.fi;
        else nnew = nnew + min1.fi;
        if (nnew < best)
            best = nnew;
    }
    printf("%.10lf\n", (double)best);
}
