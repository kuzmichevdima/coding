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
    int a1, b1, c1, L;
    scanf("%d%d%d%d", &a1, &b1, &c1, &L);
    i64 ans = 0;
    forn(delta, L + 1)
    {
        int a = a1 + delta;
        int lower1 = max((int)0, c1 - b1 - a + 1);
        int upper1 = a + c1 - b1 - 1;
        int lower2 = max((int)0, a - b1 - c1 + 1);
        int upper2 = L - delta;
        if (lower1 > upper1 || lower2 > upper2)
            continue;
        printf("delta = %d lower1 = %d upper1 = %d lower2 = %d upper2 = %d\n", delta, lower1, upper1, lower2, upper2);
        int diff1 = upper1 - lower1;
        int on_odd = (abs(lower1) % 2 == 0 ? diff1 / 2 : diff1 / 2 + 1);
        int on_even = (abs(lower1) % 2 == 0 ? diff1 / 2 + 1 : diff1 / 2);
        printf("on_odd = %d on_even = %d\n", on_odd, on_even);
        int diff2 = upper2 - lower2 + 1;
        int odd, even;
        if (diff2 % 2 == 1)
        {
            if (abs(lower2) % 2 == 0)
            {
                even = diff2 / 2 + 1;
                odd = diff2 - even;
            }
            else
            {
                odd = diff2 / 2 + 1;
                even = diff2 - odd;
            }
        }
        else odd = even = diff2 / 2;
        i64 to_add = (i64)odd * on_odd + (i64)even * on_even;
        cout << "to_add" << to_add << endl;
        ans += to_add;
    }
    cout << ans << endl;
}
