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
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n, m;
        scanf("%d%d", &n, &m);
        vi a(n);
        forn(j, n)
            a[j] = j + 1;
        forn(it, m) {
            string typ;
            int p;
            cin >> typ >> p;
            if (typ == "?")
                printf("%d\n", a[p - 1]);
            else {
                forn(j, a.size())
                    if (a[j] == p)
                        a.erase(a.begin() + j);

                forn(j, a.size())
                    if (a[j] == n - p + 1)
                        a.erase(a.begin() + j);
            }
        }
    }
}
