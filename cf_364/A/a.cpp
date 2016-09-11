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
    int n, k;
    double v1, v2, l;
    cin >> n >> l >> v1 >> v2 >> k;
    double coeff = (double)k / n;
    double s = 0.0;
    double f = 1e9;
    forn(it, 10000) {
        double m = (s + f) / 2;
        double bus_time = m * coeff;
        double walk_time = m * (1 - coeff);
        double L = bus_time * v2 + walk_time * v1;
        if (L >= l)
            f = m;
        else s = m;
    }  
    printf("%.10lf\n", s);

}
