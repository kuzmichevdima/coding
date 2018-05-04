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
    int n, t, t0;
    scanf("%d%d%d", &n, &t, &t0);
    forn(i, n) {
        int m;
        scanf("%d", &m);
        int sum = 0;
        int maxx = 0;
        int answer = 0;
        forn(j, m) {
            int x;
            scanf("%d", &x);
            maxx = max(maxx, x);
            sum += x;
            int sum1;
            if (maxx > t0)
                sum1 = sum - maxx + t0;
            else sum1 = sum;
            if (sum1 <= t)
                answer = j + 1;
        }
        printf("%d\n", answer);
    }
}
