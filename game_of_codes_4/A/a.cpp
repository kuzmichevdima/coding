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

const int maxn = 1e6+5;

int a[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    forn(j, n) {
        scanf("%d", &a[j]);
    }
    sort(a, a + n);
    int ans = a[n - 1] - a[0];
    fore(last_plus, 0, n - 2) {
        int maxx = max(a[n - 1] - k, a[last_plus] + k);
        int minn = min(a[0] + k, a[last_plus + 1] - k);
        ans = min(ans, maxx - minn);
    }
    printf("%d", ans);
}
