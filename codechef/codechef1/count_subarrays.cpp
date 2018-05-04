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

void solve()
{
    scanf("%d", &n);
    forn(j, n)
    {
        scanf("%d", &a[j]);
        list.pb(mp(a[j], j));
    }
    sort(list.begin(), list.end());
    forn(j, n)
        pos[a[j].se] = j;
    forn(j, n)
    {
        int val = 1 + get(1, 0, n, pos[j]);
        ans += val;
        upd(1, 0, n, pos[j] + 1, n);
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
    scanf("%d", &t);
    forn(test, t)
        solve();
}

