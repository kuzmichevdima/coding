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
const i64 inf = 5e18;

i64 answer;
vi listx[maxn];
vi listy[maxn];
vi xuniq, yuniq;
set <int> s;
int k;
pii r[maxn];

inline bool add(int x)
{
    s.insert(x);
    return (int)s.size() <= k;
}

inline bool complex_add(vi & v, int minx, int maxx, int miny, int maxy)
{
    forn(i, v.size())
    {
        int x = r[v[i]].fi;
        int y = r[v[i]].se;
        if (x >= minx && x <= maxx && y >= miny && y <= maxy)
            break;
        else
        {
            if (!add(v[i]))
                return false;
        }
    }
    for (int i = (int)v.size() - 1; i >= 0; i--)
    {
        int x = r[v[i]].fi;
        int y = r[v[i]].se;
        if (x >= minx && x <= maxx && y >= miny && y <= maxy)
            break;
        else
        {
            if (!add(v[i]))
                return false;
        }
    }

    return true;
}

inline void check(int minx, int maxx, int miny, int maxy)
{
    s.clear();
    forn(i, minx)
        for (auto x : listx[i])
            if (!add(x))
                return;

    fore(i, maxx + 1, xuniq.size() - 1)
        for (auto x : listx[i])
            if (!add(x))
                return;

    forn(j, miny)
        for (auto y : listy[j])
            if (!add(y))
                return;
    fore(j, maxy + 1, yuniq.size() - 1)
        for (auto y : listy[j])
            if (!add(y))
                return;

    if (!complex_add(listx[minx], minx, maxx, miny, maxy))
        return;
    if (!complex_add(listx[maxx], minx, maxx, miny, maxy))
        return;
    if (!complex_add(listy[miny], minx, maxx, miny, maxy))
        return;
    if (!complex_add(listy[maxy], minx, maxx, miny, maxy))
        return;
    int deltax = xuniq[maxx] - xuniq[minx];
    if (deltax == 0)
        deltax = 2;
    if (deltax % 2 == 1)
        deltax++;
    int deltay = yuniq[maxy] - yuniq[miny];
//    printf("deltay = %d\n", deltay);
    if (deltay == 0)
        deltay = 2;
    if (deltay % 2 == 1)
        deltay++;
  //  printf("deltax = %d deltay = %d\n", deltax, deltay);
    i64 new_val = (i64)deltax * deltay;
//    printf("check minx = %d maxx = %d miny = %d maxy = %d \n", minx, maxx, miny, maxy);
  //  cout << "new_val = " << new_val << endl;
    answer = min(answer, new_val);
}

bool cmpx(int first, int second)
{
    if (r[first].fi != r[second].fi)
        assert(false);
    return r[first].se < r[second].se;
}

bool cmpy(int first, int second)
{
    if (r[first].se != r[second].se)
        assert(false);
    return r[first].fi < r[second].fi;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d%d", &n, &k);
    forn(j, n)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        r[j] = mp(x1 + x2, y1 + y2);
        xuniq.pb(r[j].fi);
        yuniq.pb(r[j].se);
    }
    sort(xuniq.begin(), xuniq.end());
    xuniq.resize(unique(xuniq.begin(), xuniq.end()) - xuniq.begin());
    sort(yuniq.begin(), yuniq.end());
    yuniq.resize(unique(yuniq.begin(), yuniq.end()) - yuniq.begin());
/*    printf("xuniq:\n");
    for (int x : xuniq)
        printf("%d ", x);
    printf("\nyuniq:\n");
    for (int y : yuniq)
        printf("%d ", y);
    printf("\n");*/
    forn(j, n)
    {
        r[j] = mp(lower_bound(xuniq.begin(), xuniq.end(), r[j].fi) - xuniq.begin(),
                lower_bound(yuniq.begin(), yuniq.end(), r[j].se) - yuniq.begin());
        listx[r[j].fi].pb(j);
        listy[r[j].se].pb(j);
    //    printf("r[%d] = %d %d\n", j, r[j].fi, r[j].se);
    }
    forn(j, xuniq.size())
        sort(listx[j].begin(), listx[j].end(), cmpx);
    forn(j, yuniq.size())
        sort(listy[j].begin(), listy[j].end(), cmpy);
    answer = inf;
//    check(0, 1, 1, 1);
  //  exit(0);
    forn(minx, min(k + 1, (int)xuniq.size()))
        fore(maxx, max(minx, (int)xuniq.size() - k - 1), xuniq.size() - 1)
            forn(miny, min(k + 1, (int)yuniq.size()))
                fore(maxy, max(miny, (int)yuniq.size() - k - 1), yuniq.size() - 1) 
                {
                    check(minx, maxx, miny, maxy);    
                }
    answer = answer / 4;
    cout << answer;
}
