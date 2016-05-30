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
    int n, J;
    scanf("1%d%d", &n, &J);
    printf("Case #1:\n");
    for (int x = (1 << (n - 1)); x < (1 << n); x++) if (x % 2 == 1) {
        vi ans;
        fore(d, 2, 10) {
            i64 y = 0;
            i64 mult = 1;
            forn(j, n) {
                y += mult * ((x >> j) & 1);
                mult *= d;
            }
            bool found = false;
            for (i64 div = 2; div * div <= y; div++) {
                if (y % div == 0) {
                    ans.pb(div);
                    found = true;
                    break;
                }
            }
            if (!found)
                break;
        }
        if (ans.size() == 9) {
            for (int j = n - 1; j >= 0; j--)
                printf("%d", (x >> j) & 1);
            for (int x : ans)
                printf(" %d", x);
            printf("\n");
            J--;  
            if (J == 0)
                break;
        }
    }
}

