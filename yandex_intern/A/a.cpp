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

typedef pair<i64, i64> mypair;

i64 gcd(i64 x, i64 y) {
    return y == 0 ? x : gcd(y, x % y);
}

void norm(mypair & p) {
    i64 g = gcd(p.fi, p.se);
    p.fi /= g;
    p.se /= g;
}

mypair add(mypair A, mypair B) {
    mypair res = mp(A.fi * B.se + A.se * B.fi, A.se * B.se);
    norm(res);
    return res;
}

int t[6];
int pol[6], pol1[6], pol2[6], der[6], fin[6];

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
    forn(j, n)
        scanf("%d", &t[j]);
    int mint = t[0];
    forn(j, n)
        mint = min(mint, t[j]);
    pol[0] = 1;
    int common_div = 1;
    forn(j, n) {
        fore(p, 0, n)
            pol1[p] = pol[p] * t[j];
        fore(p, 0, n)
            pol2[p + 1] = -pol[p];
        fore(p, 0, n)
            pol[p] = pol1[p] + pol2[p];
        common_div *= t[j];
    }
    fore(p, 0, n)
        pol[p] *= -1;
    pol[0] += common_div;

//    fore(p, 0, n)
  //      printf("pol[%d] = %d\n", p, pol[p]);

    fore(p, 1, n)
        der[p - 1] = pol[p] * p;
    fore(p, 1, n)
        fin[p] = der[p - 1];
    //fore(p, 0, n)
      //  printf("fin[%d] = %d\n", p, fin[p]);
    mypair sum = mp(0, 1);
    i64 mult = mint;
    fore(p, 0, n) {
        sum = add(sum, mp(mult * fin[p], p + 1)); 
        mult *= mint;
    }
    sum.se *= common_div;
    norm(sum);
    cout << sum.fi << "/" << sum.se;
}
