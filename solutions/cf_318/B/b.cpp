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

bool destr[maxn];
int a[maxn];
int n;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    set <pii> order;
    forn(j, n)
    {
        scanf("%d", &a[j]);
        order.insert(mp(a[j], j));
//        printf("add %d %d\n", a[j], j);
        order.insert(mp(min(j + 1, n - j), j));
  //      printf("add %d %d\n", min(j + 1, n - j), j);
    }
    int ans = 0;
    while(!order.empty())
    {
        pii p = *order.begin();       
        order.erase(order.begin());
        if (destr[p.se])
            continue;
    //    printf("p = %d %d\n", p.fi, p.se);
        ans = max(ans, p.fi);
        destr[p.se] = true;
        if (p.se != 0)
            order.insert(mp(p.fi + 1, p.se - 1));
        if (p.se != n - 1)
            order.insert(mp(p.fi + 1, p.se + 1));
    }
    printf("%d", ans);
}
