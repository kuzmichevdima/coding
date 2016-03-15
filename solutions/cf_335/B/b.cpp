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

struct Edge
{
    int w, flag, number;
    Edge(){}
};

bool operator < (Edge first, Edge second)
{
    if (first.w != second.w)
        return first.w < second.w;
    return first.flag > second.flag;
}

const int maxn = 1e5+5;

Edge e[maxn];
pii ans[maxn];
queue <pii> Q;

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
    forn(j, m)
    {
        scanf("%d%d", &e[j].w, &e[j].flag);
        e[j].number = j;
    }
    sort(e, e + m);
    int start = 0;
    int got = 0;
    while(start < m)
    {
        int last = start;
        while(last + 1 < m && e[last + 1].w == e[last].w)
            last++;
        fore(i, start, last)
        {
//            printf("process i = %d\n", i);
            if (e[i].flag == 1)
            {
                fore(j, 2, got + 1)
                {
                    if ((int)Q.size() > m)
                        break;
                    Q.push(mp(got + 2, j));
                }
                got++;
                ans[e[i].number] = mp(1, got + 1);
            }
            else
            {
                if (Q.empty())
                {
                    printf("-1");
                    exit(0);
                }
                ans[e[i].number] = Q.front();
                Q.pop();
            }
        }
        start = last + 1;
    }
    if (got != n - 1)
    {
        printf("-1");
        exit(0);
    }
    forn(j, m)
        printf("%d %d\n", ans[j].fi, ans[j].se);
}
