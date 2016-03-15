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

const int maxn = 2e5+5;

int a[maxn];
pii b[maxn];
int ans[maxn];
int n, m;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    forn(j, n)
        scanf("%d", &a[j]);
    forn(j, m)
    {
        scanf("%d", &b[j].fi);
        b[j].se = j;
    }
    sort(a, a + n);
    sort(b, b + m);
    int pointer = 0;
    forn(j, m)
    {
        while(pointer < n && a[pointer] <= b[j].fi)
            pointer++;
        ans[b[j].se] = pointer;
    }
    forn(j, m)
        printf("%d ", ans[j]);
}
