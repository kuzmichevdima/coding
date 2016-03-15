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

pii a[maxn];
int x[maxn];
int pos[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(j, n)
    {
        scanf("%d", &a[j].fi);
        a[j].se = j;
     //   coord[j] = a[j].fi;
    }
    sort(a, a + n);
    forn(j, n)
    {
        pos[a[j].se] = j;
        x[j] = a[j].fi;
    }
    forn(q, m)
    {
        int cur, L;
        scanf("%d%d", &cur, &L);
        cur = pos[cur - 1];
        //printf("cur = %d L = %d\n", cur, L);
        int next = upper_bound(x, x + n, L + x[cur]) - x - 1;
        L -= a[next].fi - a[cur].fi;
        cur = next;
        int dir = -1;
        while(L > 0)
        {
            if (dir == 1)
                next = upper_bound(x, x + n, x[cur] + L) - x - 1;
            else next = lower_bound(x, x + n, x[cur] - L) - x;
            if (next == cur)
                break;
            int dist = abs(x[cur] - x[next]);
            if ((L / dist) % 2 == 1)
            {
                cur = next;
                dir = -dir;
            }
            L = L % dist;
        }
        printf("%d\n", a[cur].se + 1);
    }
}
