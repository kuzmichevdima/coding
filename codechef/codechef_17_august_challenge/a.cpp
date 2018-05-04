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
        int n;
        scanf("%d", &n);
        vi a(n);
        forn(j, n)
            scanf("%d", &a[j]);
        int cur = 0;
        vi A(8);
        fore(i, 1, 7) {
            while(cur < n && a[cur] == i) {
                cur++;
                A[i]++;
            }
            //printf("A[%d] = %d\n", i, A[i]);
        }
        bool fail = false;
        for (int i = 6; i >= 1; i--) {
            //printf("i = %d cur = %d A = %d fail = %d\n", i, cur, A[i], fail);
            forn(iter, A[i])
                if (cur == n || a[cur] != i) {
                    fail = true;
                    break;
                } else cur++;
        }
        fail |= (cur != n);
        if (fail)
            printf("no\n");
        else printf("yes\n");
    }
}

