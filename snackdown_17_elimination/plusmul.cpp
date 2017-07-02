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

const i64 mod = 1e9+7;

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
        i64 sum_dp = 0;
        i64 sum_add = 1;
        i64 p = 1;
        forn(i, n) {
            int val;
            scanf("%d", &val);
            sum_add = (sum_add * val) % mod;
            i64 newdp = (sum_dp + sum_add) % mod;
            if (i == n - 1)
                cout << newdp << endl;
            else {
                sum_dp = (sum_dp + newdp) % mod;
                sum_add = (sum_add  + p) % mod;
            }
            p = p * 2 % mod;
        }

    }
}

