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

const int maxn = 30;
const int inf = 2e9;

int part, limit;
map <pii, pii> M[2];
int delta[maxn][4];
int n;

void go(int s, int x1, int x2, int x3, int prof)
{
    if (s == limit)
    {
        pii p = (part == 0 ? mp(x1 - x2, x2 - x3) : mp(x2 - x1, x3 - x2));
        auto f = M[part].find(p);
        if (f == M[part].end())
            M[part][p] = mp(x1, prof);
        else if (f->se.fi < x1)
            M[part][p] = mp(x1, prof);
        return;
    }
    go(s + 1, x1 + delta[s][1], x2 + delta[s][2], x3, prof * 3);
    go(s + 1, x1 + delta[s][1], x2, x3 + delta[s][3], prof * 3 + 1);
    go(s + 1, x1, x2 + delta[s][2], x3 + delta[s][3], prof * 3 + 2);
}

string get(int prof, int len)
{
    string res = "";
    forn(j, len)
    {
        if (prof % 3 == 0)   
            res = "LM" + res;
        else if (prof % 3 == 1)
            res = "LW" + res;
        else res = "MW" + res;
        prof /= 3;
    }
    return res;
}

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
    {
        fore(h, 1, 3)
            scanf("%d", &delta[j][h]);
    }
    part = 0;
    limit = n / 2;
    go(0, 0, 0, 0, 0);
    part = 1;
    limit = n;
    go(n / 2, 0, 0, 0, 0);
    int best = -inf;
    string ans_str;
   // for (auto elem : M[1])
     //   printf("in M[1] %d %d %d %d\n", elem.fi.fi, elem.fi.se, elem.se.fi, elem.se.se);
    for (auto elem : M[0])
    {
        pii X = elem.fi;
     //   printf("in M[0] %d %d\n", X.fi, X.se);
        auto iter = M[1].find(X);
        if (iter == M[1].end())
            continue;
        pii addit = elem.second;
        int nnew = iter->second.first + addit.first;
        if (nnew > best)
        {
            best = nnew;
            ans_str = get(addit.second, n / 2) + get(iter->second.second, n - n / 2); 
        }
    }
    if (best == -inf)
    {
        printf("Impossible");
        exit(0);
    }
   // printf("best = %d\n", best);
    forn(j, n)
       cout << ans_str.substr(j * 2, 2) << endl;
}
