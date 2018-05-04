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

int a[3];

i64 get(int x)
{
    if (x < 0)
        return 0;
    return (i64)(x + 2) * (x + 1) / 2;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int L;
    scanf("%d%d%d%d", &a[0], &a[1], &a[2], &L);
    i64 total = (i64)(L + 3) * (L + 2) * (L + 1) / 6;
    forn(chosen, 3)
        forn(La, L + 1)
        {
            int tmp = a[chosen];
            forn(j, 3) if (j != chosen)
                tmp -= a[j];
            i64 to_sub = get(min(L - La, tmp + La));
            total -= to_sub;
        }
    cout << total;
}

