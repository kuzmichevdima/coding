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

/*vi primes;

void precalc()
{
    fore(i, 2, con) if (!used[i])
    {
        primes.pb(i);
        for (int j = 2 * i; j <= con; j += i)
            used[j] = true;
    }
}

int get(
*/
int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
//    precalc();
    int n;
    scanf("%d", &n);
    int canonical;
    forn(j, n)
    {
        int x;
        scanf("%d", &x);
        if (j == 0)
        {
            canonical = x;
            while(canonical % 2 == 0)
                canonical /= 2;
            while(canonical % 3 == 0)
                canonical /= 3;
        }
        else
        {
            while(x % 2 == 0)
                x /= 2;
            while(x % 3 == 0)
                x /= 3;
            if (x != canonical)
            {
                printf("No");
                exit(0);
            }
        }
    }
    printf("Yes");
}
