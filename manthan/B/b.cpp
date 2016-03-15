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

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int cnt2 = 0;
    int cnt5 = 0;
    int m;
    scanf("%d", &m);
    vi ans;
    fore(j, 2, 10000000)
    {
        int x = j;
        while(x % 2 == 0)
        {
            cnt2++;
            x /= 2;
        }
        while(x % 5 == 0)
        {
            x /= 5;
            cnt5++;
        }
        if (min(cnt2, cnt5) == m)
        {
            ans.pb(j);
        }
    }
    printf("%d\n", (int)ans.size());
    for (int x : ans)
        printf("%d ", x);
}
