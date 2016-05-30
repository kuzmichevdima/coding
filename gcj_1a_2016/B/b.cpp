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
//    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    set <int> S;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        S.clear();
        int n;
        scanf("%d", &n);
        forn(i, 2 * n - 1)
            forn(j, n)
            {
                int x;
                scanf("%d", &x);
                if (S.find(x) != S.end())
                    S.erase(x);
                else S.insert(x);
            }
        printf("Case #%d: ", test);
        for (int x : S)
            printf("%d ", x);
        printf("\n");

    }
}
