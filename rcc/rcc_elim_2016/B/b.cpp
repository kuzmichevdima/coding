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

const int maxn = 1e5+5;

pii a[maxn];

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
        int sum, n;
        scanf("%d%d", &sum, &n);
        forn(j, n) {
            scanf("%d%d", &a[j].fi, &a[j].se);

        }
        sort(a, a + n);
        multiset <int> s;
        pii answer = mp(-1, -1);
        forn(i, n) {
            s.insert(a[i].se);
            int limit = sum - a[i].fi;
            while(!s.empty() && *s.rbegin() > limit) {
                s.erase(*s.rbegin());
            }
            if (answer.fi < (int)s.size()) {
                answer = mp(s.size(), i);
            }
        }
        printf("%d %d\n", a[answer.se].fi, sum - a[answer.se].fi);
    }
}