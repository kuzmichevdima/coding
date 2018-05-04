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

const int maxn = 5e5+5;

int a[maxn];
int n, k;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    i64 sum = 0;
    forn(j, n) {
        scanf("%d", &a[j]);
        sum += a[j];
    }
    sort(a, a + n);
    int s = 0;
    int f = 2e9;
    while(s < f) {
        int m = ((i64)s + f) / 2 + 1;
        //int m = (s + f) / 2 + 1;
        //printf("%d %d %d\n", s, f, m);
        int cnt = k;
        forn(j, n) {
            if (a[j] >= m)
                break;
            cnt -= (m - a[j]);
            if (cnt < 0)
                break;
        }
        if (cnt >= 0) {
            s = m;
        }
        else f = m - 1;
    }
    int minn = s;

    s = 0;
    f = 2e9;
    while(s < f) {
        int m = ((i64)s + f) / 2;
        int cnt = k;
        for(int j = n - 1; j >= 0; j--) {
            if (a[j] <= m)
                break;
            cnt -= (-m + a[j]);
            if (cnt < 0)
                break;
        }
        if (cnt >= 0) {
            f = m;
        }
        else s = m + 1;
    }
    int maxx = s;
    //printf("minn = %d maxx = %d\n", minn, maxx);
    if (maxx <= minn) {
        if (sum % n == 0)
            printf("0\n");
        else printf("1\n");
    }
    else printf("%d\n", maxx - minn);
}
