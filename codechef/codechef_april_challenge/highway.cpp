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

const double eps = 1e-6;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n, speed, width;
        scanf("%d%d%d", &n, &speed, &width);
        vi v(n);
        forn(i, n)
            scanf("%d", &v[i]);
        vi d(n);
        forn(i, n)
            scanf("%d", &d[i]);
        vi s(n);
        forn(i, n)
            scanf("%d", &s[i]);
        vi len(n);
        forn(i, n)
            scanf("%d", &len[i]);
        double time_to_cross = (double)width / speed;
        //printf("time_to_cross = %.5lf\n", time_to_cross);
        double cur = 0;
        forn(i, n) {
            double start, finish;
            if (d[i] == 1) {
                if (s[i] > 0) {
                    cur += time_to_cross;
                    continue;
                }
            } else {
                if (s[i] < 0) {
                    cur += time_to_cross;
                    continue;
                }
            }
            start = (double)abs(s[i]) / v[i];        
            finish = (double)(abs(s[i]) + len[i]) / v[i];
            if (start - cur - time_to_cross > eps)
                cur += time_to_cross;
            else cur = max(cur, finish) + time_to_cross;
            //cur = max(cur, finish) + time_to_cross;
            //start -= (i + 1) * time_to_cross;
            //finish -= i * time_to_cross;
            // printf("start = %.5lf finish = %.5lf\n", start, finish);
        }
        printf("%.10lf\n", cur);
    }
}

