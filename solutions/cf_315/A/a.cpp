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

const int con = 15e5;

bool mark[con + 5];

bool prime(int n)
{
    if (n == 1)
        return false;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return false;
    return true;
}

bool pal(int n)
{
    vi v;
    while(n > 0)
    {
        v.pb(n % 10);
        n /= 10;
    }
    forn(j, v.size() / 2)
        if (v[j] != v[(int)v.size() - j - 1])
            return false;
    return true;
}

void precalc()
{
    mark[1] = true;
    fore(i, 2, con) if (!mark[i])
    {
        for (int j = 2 * i; j <= con; j += i)
            mark[j] = true;
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    precalc();
    int P, Q;
    scanf("%d%d", &P, &Q);
    int n = 1;
    int cnt_prime = 0;
    int cnt_pal = 0;
    int ans;
    while(n < con)
    {
        if (!mark[n])
        {
            cnt_prime++;
     //       printf("prime %d\n", n);
        }
        if (pal(n))
        {
            cnt_pal++;
       //     printf("pal %d\n", n);
        }
        if (cnt_prime * Q <= P * cnt_pal)
        {
         //   printf("%d\n", n - 1);
            ans = n;
        }
        n++;
    }
    printf("%d\n", ans);
}
