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

void imp() {
    printf("-1");
    exit(0);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int a, b, k;
    scanf("%d%d%d", &k, &a, &b);
    int tmp = a / k + b / k;
    int ans = 0;
    if (a % k != 0) {
        a -= a % k;
        b -= k;
        if (b < 0)
            imp();
        ans++;
    }
    if (b % k != 0) {
        a -= k;
        b -= b % k;
        if (a < 0)
            imp();
        ans++;
    }
    ans += (a + b) / k;
    printf("%d", ans);
    printf("\n%d ?", tmp);
}
