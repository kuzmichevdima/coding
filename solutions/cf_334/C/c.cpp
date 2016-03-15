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

int get(int x)
{
    if (x == 1)
        return 1;
    if (x == 2)
        return 0;
    if (x == 3)
        return 1;
    if (x % 2 == 1)
        return 0;
    int first = get(x / 2);
    int second = get(x - 1);
    forn(j, 3)
        if (first != j && second != j)
            return j;
    assert(false);
 }

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    int res = 0;
    forn(j, n)
    {
        int x;
        scanf("%d", &x);
        int nnew;
        if (k % 2 == 0)
        {
            if (x == 1)
                nnew = 1;
            else if (x == 2)
                nnew = 2;
            else if (x % 2 == 0)
                nnew = 1;
            else nnew = 0;
        }
        else
        {
            nnew = get(x);
        }
//        printf("x = %d nnew = %d\n", x, nnew);
        res ^= nnew;
    }
    if (res)
        printf("Kevin");
    else printf("Nicky");
}
