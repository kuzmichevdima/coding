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
    int n;
    scanf("%d", &n);
    vi a(n), b(n);
    forn(i, n) {
        scanf("%d", &a[i]);
        if (i == 0)
            b[i] = 1;
        else b[i] = b[i - 1];
        b[i] = max(b[i], a[i] + 1);
    }
    int maxx = -1e9;
    i64 ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        maxx = max(maxx, b[i] - i);
        b[i] = max(b[i], i + maxx);
        ans += b[i] - a[i] - 1;
    }
    cout << ans;

}

