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

const int maxn = 5e5+5;

int a[maxn];
vector <pii> list;
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
    forn(j, n)
        scanf("%d", &a[j]);
    int start = 0;
    fore(p, 1, n - 1)
    {
        if (a[p] == a[p - 1])
        {
            if (start == -1)
            {
                start = p - 1;      
            }
        }
        else if (start != -1)
        {
            list.pb(mp(start, p - 1));
            start = -1;
        }
    }
    if (start == -1)
        start = n - 1;
    list.pb(mp(start, n - 1));
  /*  printf("list size = %d\n", (int)list.size());
    forn(j, list.size())
        printf("%d %d\n", list[j].fi, list[j].se);*/
    int ans = 0;
    forn(j, (int)list.size() - 1) if (list[j].se != list[j + 1].fi - 1)
    {
        int cnt0 = 0;
        int cnt1 = 0;
        fore(i, list[j].se + 1, list[j + 1].fi - 1)
            if (a[i] == 0)
                cnt0++;
            else cnt1++;
//        printf("j = %d cnt0 = %d cnt1 = %d\n", j, cnt0, cnt1);
        if (cnt0 == cnt1)
        {
            ans = max(ans, cnt0);
            fore(i, list[j].se + 1, list[j].se + cnt0)
                a[i] = a[list[j].se];
            fore(i, list[j].se + cnt0 + 1, list[j + 1].fi - 1)
                a[i] = a[list[j + 1].fi];
        }
        else if (cnt1 > cnt0)
        {
            ans = max(ans, cnt1);
            fore(i, list[j].se + 1, list[j + 1].fi - 1)
                a[i] = 0;
        }
        else
        {
            ans = max(ans, cnt0);
            fore(i, list[j].se + 1, list[j + 1].fi - 1)
                a[i] = 1;
        }
    }
    printf("%d\n", ans);
    forn(j, n)
        printf("%d ", a[j]);
}
