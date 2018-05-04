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

multiset <int> S;

int gcd(int x, int y)
{
    return (x == 0 ? y : gcd(y % x, x));
}

const int maxn = 505 * 505;

int a[maxn];
int ans[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    n = n * n;
    forn(j, n)
    {
       scanf("%d", &a[j]);
       S.insert(a[j]);
    }
    /*sort(a, a + n);
    for (int j = n - 1; j >= 0; j--)
    {
          
    }*/
    int done = 0;
    while(!S.empty())
    {
        int x = *S.rbegin();
        S.erase(S.find(x));
  //      printf("x = %d\n", x);
        forn(j, done)
            forn(iter, 2)
            {
                int tmp = gcd(x, ans[j]);
//                printf("to erase %d (gcd of %d and %d)\n", tmp, x, ans[j]);
                S.erase(S.find(tmp));
            }
        ans[done] = x;
 //       printf("add %d to answer\n", x);
        done++;
    }
    assert(done * done == n);
    forn(j, done)
        printf("%d ", ans[j]);
}
