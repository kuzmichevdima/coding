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

const int maxn = 1e6;
const int MOD = 1e9+7;

int fact[maxn + 5];
pii poly[maxn + 5];

inline int mult(int x, int y) {
    return (i64)x * y % MOD;
}

/*int bin_pow(int x, int p) {
    if (p == 0)
        return 1;
    int y = bin_pow(x, p / 2);
    y = mult(y, y);
    if (p & 1)
        y = mult(y, x);
    return y;
}*/

int bin_pow(int x, int p) {
    int result = 1;
    while(p) {
        if (p & 1)
            result = (i64)(result) * x % MOD;
        x = (i64)x * x % MOD;
        p >>= 1;
    }
    return result;
}

int rev(int x) {
    return bin_pow(x, MOD - 2);
}

int place(int x, int d) {
    return (mult(poly[x].fi, d) + poly[x].se) % MOD;
}

int get_pref(int x, int d) {
    int real_val = place(x, d);
//    printf("x = %d d = %d real_val = %d\n", x, d, real_val);
    return (i64)fact[x + 1] * rev(real_val) % MOD; 
}

int first_query(int L, int R, int d) {
    int part1 = get_pref(R, d);
    int part2 = get_pref(L - 1, d);
    return mult(part1, rev(part2));
}

void precalc() {
    fact[1] = 1;
    fore(j, 2, maxn + 1)
        fact[j] = (i64)fact[j - 1] * j % MOD;
    poly[0] = mp(1, 0);
    poly[1] = mp(1, 1);
    fore(n, 2, maxn + 1) {
        poly[n] = mp(((i64)n * poly[n - 2].fi + poly[n - 1].fi) % MOD,
                ((i64)n * poly[n - 2].se + poly[n - 1].se) % MOD);
        //if (n <= 4)
        //    printf("poly[%d] = %d %d\n", n, poly[n].fi, poly[n].se);
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    precalc();
    int Q;
    scanf("%d", &Q);
    forn(query, Q) {
        int typ;
        scanf("%d", &typ);
        if (typ == 1) {
            int L, R;
            i64 d;
            cin >> L >> R >> d;
            int res = first_query(L, R, d % MOD);
            printf("%d\n", res);
        } else {
            int n, m;
            i64 d;
            cin >> n >> m >> d;
            int ans = 1;
            for (i64 d1 = d; d1 <= d + m; d1++) {
                int part = first_query(n, n, d1 % MOD);
                ans = mult(ans, part);
            }
            printf("%d\n", ans);
        }
    }
}
