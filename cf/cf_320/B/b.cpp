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

const int maxn = 2e5 + 5;

i64 a[maxn];
i64 pref[maxn];
i64 suff[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int k, x, n;
    scanf("%d%d%d", &n, &k, &x);
    forn(j, n)
        cin >> a[j];
    pref[0] = a[0];
    fore(j, 1, n - 1)
        pref[j] = pref[j - 1] | a[j];
    suff[n - 1] = a[n - 1];
    for (int j = n - 2; j >= 0; j--)
        suff[j] = suff[j + 1] | a[j];
    i64 best = 0;
    forn(center, n)
    {
        i64 nnew = a[center];
        forn(iter, k)
            nnew *= x;
        if (center != 0)
            nnew |= pref[center - 1];
        if (center != n - 1)
            nnew |= suff[center + 1];
        best = max(best, nnew);
    }
    cout << best;
}
