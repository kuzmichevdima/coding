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

const int maxn = 2005;
const i64 CON = 2e9+5;

pii a[maxn];

vector <i64> lst;
i64 b[maxn][maxn];
int cnt[maxn * maxn];

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
        scanf("%d%d", &a[j].fi, &a[j].se);
    forn(i, n)
        forn(j, n) if (i != j) {
            b[i][j] = CON * (a[j].fi - a[i].fi) + (a[j].se - a[i].se);
            lst.pb(b[i][j]);
        }
    sort(lst.begin(), lst.end());
    lst.resize(unique(lst.begin(), lst.end()) - lst.begin());

    forn(i, n)
        forn(j, n) if (i != j) {
            cnt[lower_bound(lst.begin(), lst.end(), b[i][j]) - lst.begin()]++;
        }
    i64 ans = 0;
    forn(i, lst.size())
        ans += (i64)cnt[i] * (cnt[i] - 1);
    ans /= 8;
    cout << ans;
}
