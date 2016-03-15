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

i64 a[100][100];

i64 get(int n, int k)
{
    if (a[n][k] != 0)
        return a[n][k];
    if (k == 1)
        return a[n][k] = n;
    return a[n][k] = get(n - 1, k - 1) * get(n, k - 1) / (get(n, k - 1) - get(n - 1, k - 1));
}

i64 gcd(i64 x, i64 y)
{
    return (x == 0 ? y : gcd(y % x, x));
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    //int L = 4;
    fore(n, 1, 15)
    {
        printf("\n=============\nn = %d\n", n);
        i64 cur = 1;
        fore(k, 1, n)
        {
            i64 g = get(n, k);
            cur = cur * g / gcd(cur, g);
            if (k > 1 && k <= n / 2)
            {
                i64 tr = (n % (k - 1) == 0 ? g :  g * (k - 1));
                printf("k = %d %lld cur = %lld tr = %lld\n", k, g, cur, tr);
                assert(tr == cur);
            }
        }
    }
}

