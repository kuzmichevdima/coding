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

const int delta = 500;
const int lines = 2001;
const int maxn = 1e6+5;

vector <pii> list[lines + 5];
int x[maxn];
int y[maxn];
i64 total;
vi ans;

void add(int number)
{
    if (!ans.empty())
    {
        int addit = abs(x[ans.back()] - x[number]) + abs(y[ans.back()] - y[number]);
//        printf("+ %d\n", addit);
        total += addit;
    }
    ans.pb(number);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    //n = 1e6;
    scanf("%d", &n);
    int mod = 1e6;
    forn(j, n)
    {
        scanf("%d%d", &x[j], &y[j]);
//        x[j] = rand() % mod;
  //      y[j] = rand() % mod;
//        printf("x = %d y = %d\n", x[j], y[j]);
        list[y[j] / delta].pb(mp(x[j], j));
    }
    forn(j, lines) if (!list[j].empty())
    {
        sort(list[j].begin(), list[j].end());
  /*      printf("line %d\n", j);
        for (pii p : list[j])
            printf("%d %d\n", p.fi, p.se);*/
        if (j % 2 == 0)
        {
            for (auto p : list[j])
                add(p.se);
  //              ans.pb(p.se);
        }
        else
        {
            for (int h = list[j].size() - 1; h >= 0; h--)
                add(list[j][h].se);
//                ans.pb(list[j][h].se);
        }
    }
    assert((int)ans.size() == n);
   /* total = 0;
    forn(j, n - 1)
    {
        total += abs(x[ans[j]] - x[ans[j + 1]]) + abs(y[ans[j]] - y[ans[j + 1]]);
    }*/
    //cout << "total = " << total << endl;
    for (int x : ans)
        printf("%d ", x + 1);
}
