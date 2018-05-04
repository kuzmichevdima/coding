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

const int maxn = 150005;

int t[maxn];
set <pii> order;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k, q;
    scanf("%d%d%d", &n, &k, &q);
    fore(i, 1, n)
        scanf("%d", &t[i]);
    forn(query, q)
    {
        int typ, id;
        scanf("%d%d", &typ, &id);
        if (typ == 1)
        {
            order.insert(mp(-t[id], id));
            if ((int)order.size() > k)
                order.erase(*order.rbegin());
        }
        else
        {
            if (order.find(mp(-t[id], id)) == order.end())
                    printf("NO\n");
            else printf("YES\n");
        }

    }
}
