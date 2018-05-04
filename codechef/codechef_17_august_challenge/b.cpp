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

const int maxn = 1e5 + 5;

i64 a[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n, d;
        scanf("%d%d", &n, &d);
        i64 sum = 0;
        forn(i, n) {
            cin >> a[i];
            sum += a[i];
        }
        if (sum % n != 0) {
            printf("-1\n");
            continue;
        }
        int fin = sum / n;
        i64 ans = 0;
        fore(i, 0, n - d - 1) {
            i64 delta = -a[i] + fin;
            ans += abs(delta);
            a[i] += delta;
            a[i + d] -= delta;
        }
        bool fail = false;
        fore(i, n - d, n - 1)
            if (a[i] != fin) {
                fail = true;
                break;
            }
        if (fail)
            printf("-1\n");
        else cout << ans << endl;
    }
}

