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

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int ans = 0;
    fore(x1, 0, n)
        fore(y1, 0, m)
            fore(x2, 0, n)
                fore(y2, 0, m) {
                    if (x1 == x2 && y1 == y2)
                        continue;
                    int deltax = abs(x1 - x2);
                    int deltay = abs(y1 - y2);
                    int g = gcd(deltax, deltay);
                    //printf("%d %d -> %d %d cnt = %d\n", x1, y1, x2, y2, cnt);
                    if (g + 1 == k) {
                        ans++;
                    }
                }
    ans /= 2;
    printf("%d", ans);
}

