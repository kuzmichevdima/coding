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

const int maxn = 1e5+5;
const i64 inf = 1e18;

int a[maxn];

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
    i64 ans = -inf;
    i64 cur_odd = 0;
    i64 cur_even = 0;
    i64 min_odd = 0;
    i64 min_even = inf;
    forn(j, n)
        scanf("%d", &a[j]);
    fore(j, 1, n - 1) {
        int delta = abs(a[j] - a[j - 1]);
        if (j % 2) {
            cur_odd += delta;
            cur_even -= delta;
        } else {
            cur_odd -= delta;
            cur_even += delta;
        }
        ans = max(ans, cur_odd - min_odd);
        ans = max(ans, cur_even - min_even);

        min_odd = min(min_odd, cur_odd);
        min_even = min(min_even, cur_even);
    }
    cout << ans;
}
