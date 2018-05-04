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
    int n, h;
    scanf("%d%d", &n, &h);
    vi a(n);
    vi b(n);
    forn(i, n) {
        scanf("%d%d", &a[i], &b[i]);
    }
    int maxx = a[0];
    forn(i, n)
        maxx = max(maxx, a[i]);
    vi bestb;
    forn(i, n)
        if (b[i] > maxx)
            bestb.pb(b[i]);
    sort(bestb.begin(), bestb.end());
    reverse(bestb.begin(), bestb.end());
    int ans = 0;
    forn(j, bestb.size()) {
        h -= bestb[j];
        ans++;
        if (h <= 0)
            break;
    }
    if (h > 0) {
        ans += h / maxx;
        if (h % maxx != 0)
            ans++;
    }
    printf("%d", ans);
}

