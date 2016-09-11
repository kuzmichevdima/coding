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
        i64 n, k;
        int b;
        cin >> n >> k >> b;
        bool fail = false;
        vector <i64> ans;
        for (int box = b; box >= 1; box--) {
            i64 small_sum = (i64)(1 + box - 1) * (box - 1) / 2;
            i64 next = min(k, n - small_sum);
            if (next >= 1) {
                k = next - 1;
                n -= next;
               ans.pb(next); 
            } else {
                fail = true;
                break;
            }
        }
        if (fail || n != 0) {
            printf("-1\n");
            continue;
        }
        for (int ind = b - 1; ind >= 0; ind--) {
            cout << ans[ind];
            if (ind != 0)
                cout << " ";
        }
        printf("\n");
    }
}
