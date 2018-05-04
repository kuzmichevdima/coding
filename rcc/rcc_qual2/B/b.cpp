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

const int maxn = 105;

int a[maxn];
int b[maxn];

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
        int n, m;
        scanf("%d%d", &n, &m);
        forn(j, n)
            scanf("%d", &a[j]);
        forn(j, m)
            scanf("%d", &b[j]);
        sort(a, a + n);
        sort(b, b + m);
        reverse(a, a + n);
        string str;
        cin >> str;
        int cur = 0;
        int pointera = 0;
        int pointerb = 0;
        int ans = 0;
        forn(day, n + m) {
            if (str[day] == '+') {
                cur += a[pointera];
                pointera++;
            } else {
                if (cur >= b[pointerb]) {
                    cur -= b[pointerb];
                    pointerb++;
                } else ans++;
            }
        }
        printf("%d\n", ans);
    }
}
