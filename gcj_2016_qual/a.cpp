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

bool mark[10];

int main() {
#ifdef LOCAL
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        memset(mark, false, sizeof(mark));
        int n;
        scanf("%d", &n);
        if (n == 0) {
            printf("Case #%d: INSOMNIA\n", test);
            continue;
        }
        int cur = n;
        while(true) {
            int tmp = cur;
            while(tmp > 0) {
                mark[tmp % 10] = true;
                tmp /= 10;
            }
            bool ok = true;
            forn(j, 10)
                if (!mark[j]) {
                    ok = false;
                    break;
                }
            if (ok) {
                printf("Case #%d: %d\n", test, cur);
                break;
            }
            cur += n;
        }
    }
}

