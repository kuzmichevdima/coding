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

const i64 inf = 1e18;

map <int, int> M;
map <int, int> M2;
int n, m, k;

inline i64 get(int val, int add) {
    while (val < 0)
        val += 2 * n;
    while (val >= 2 * n)
        val -= 2 * n;
    if (M.find(val) == M.end())
        return inf;
    i64 result = 2 * (i64)M[val] * m + add;
    if (result <= 0)
        return 2 * (i64)M2[val] * m + add;
    else return result;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
/*    n = 1e5;
    m = 1e5;
    k = 1e5;*/
    forn(k2, 2 * n) {
        //cout << 2 * (i64)k2 * m << endl;
        int r = (i64)k2 * 2 * m % (2 * n);
        if (M.find(r) == M.end())
            M[r] = k2;
        else if (M2.find(r) == M2.end())
            M2[r] = k2;
    }
    forn(q, k) {
        int x, y;
        scanf("%d%d", &x, &y);
        //x = 1;
        //y = m - 1;
        i64 g1 = get(x + y, -y);
        i64 g2 = get(x - y, y);
        i64 g3 = get(y - x, -y);
        i64 g4 = get(-x-y, y);
        i64 ans = min(min(g1, g2), min(g3, g4));
        if (ans == inf)
            cout << -1 << '\n';
        else cout << ans << '\n';
    }
}
