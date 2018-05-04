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
    int n;
    scanf("%d", &n);
    vi a(n);
    forn(j, n)
        scanf("%d", &a[j]);
    vi ans;
    forn(j, n) {
        ans.pb(a[j]);    
        if (j != n - 1 && __gcd(a[j], a[j + 1]) != 1) {
            for (int chosen = 2; true; chosen++)
                if (__gcd(a[j], chosen) == 1 && __gcd(a[j + 1], chosen) == 1) {
                    ans.pb(chosen);
                    break;
                }
        }
    }
    printf("%d\n", (int)ans.size() - n);
    for (int x : ans)
        printf("%d ", x);
}
