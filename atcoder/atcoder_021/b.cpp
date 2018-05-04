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

typedef pair<double, int> mypair;

const int maxn = 105;
const double PI = 3.14159265359;
pii p[maxn];

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
    forn(i, n) {
        scanf("%d%d", &p[i].fi, &p[i].se);
    }
    forn(i, n) {
        vector<mypair> events;
        forn(j, n) {
            if (i == j)
                continue;
            int deltax = p[j].fi - p[i].fi;
            int deltay = p[j].se - p[i].se;
            double alpha = atan2(deltay, deltax);
            double fin = alpha + PI;
            if (fin < PI) {
                events.pb({alpha, +1});
                events.pb({fin, -1});
            } else {
                events.pb({alpha, +1});
                events.pb({PI, -1});
                events.pb({-PI, +1});
                events.pb({fin - 2 * PI, -1});
            }
        }
        sort(events.begin(), events.end());
        double s = 0.0;
        int balance = 0;
        double prev = 0;
        for (mypair& p : events) {
            if (balance == n - 1)
                s += p.fi - prev;
            prev = p.fi;
            balance += p.se;
        }
        printf("%.10lf\n", s / (2 * PI));
    }
}

