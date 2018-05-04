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
    i64 p, q, r;
    int n;
    cin >> n >> p >> q >> r;
    vi a(n);
    forn(i, n) {
        scanf("%d", &a[i]);
    }
    vi max_pref(n), min_pref(n), max_suff(n), min_suff(n);
    forn(i, n) {
        max_pref[i] = (i == 0 ? a[0] : max(max_pref[i - 1], a[i]));
        min_pref[i] = (i == 0 ? a[0] : min(min_pref[i - 1], a[i]));
    }
    for (int i = n - 1; i >= 0; i--) {
        max_suff[i] = (i == n - 1 ? a[n - 1] : max(max_suff[i + 1], a[i]));
        min_suff[i] = (i == n - 1 ? a[n - 1] : min(min_suff[i + 1], a[i]));
    }
    i64 ans;
    forn(j, n) {
        i64 nnew = q * a[j] + (p >= 0 ? p * max_pref[j] : p * min_pref[j]) + (r >= 0 ? r * max_suff[j] : r * min_suff[j]);
        if (j == 0)
            ans = nnew;
        else
            ans = max(ans, nnew);
    }
    cout << ans;
}

