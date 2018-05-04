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

int mod;

inline void addmod(int& x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}

inline int bin_pow(int x, int y) {
    int res = 1;
    int mult = x;
    while(y) {
        if (y & 1)
            res = (i64)res * mult % mod;
        y /= 2;
        mult = (i64)mult * mult % mod;
    }
    return res;
}

int ez_sol(int n) {
    int res = 0;
    fore(j, 0, n) {
        addmod(res, bin_pow(j, j));
    }
    return res;
}

int get(int n) {
    if (mod == 1)
        return 0;
    int ans = 0;
    forn(k, min(n + 1, mod)) {
        int cur = bin_pow(k, k);
        int mult = bin_pow(k, mod);
        vi list;
        list.pb(cur);
        int sum = cur;
        bool found = false;
        vi pos(mod, -1);
        pos[cur] = 0;
        for (int j = k + mod; j <= n; j += mod) {
            cur = (i64)list.back() * mult % mod;
            //printf("k = %d j = %d cur = %d\n", k, j, cur);
            if (pos[cur] != -1) {
                found = true;
                int total = (n - j) / mod + 1;
                int len = (int)list.size() - pos[cur];
                int full = total / len + 1;
                //printf("found! pos[%d] = %d len = %d full = %d total = %d\n", cur, pos[cur], len, full, total);
                //printf("full = %d\n", full);
                int on_loop = 0;
                fore(j, pos[cur], (int)list.size() - 1)
                    addmod(on_loop, list[j]);
                addmod(ans, (i64)on_loop * full % mod);
                forn(h, pos[cur])
                    addmod(ans, list[h]);
                //printf("on_loop = %d ans here = %d\n", on_loop, ans);
                forn(h, total % len)
                    addmod(ans, list[h + pos[cur]]);
                break;
            }
            pos[cur] = list.size();
            list.pb(cur);
            addmod(sum, cur);
        }
        if (!found) {
            //printf("k = %d not found adding %d\n", k, sum);
            addmod(ans, sum);
        }
        //printf("after k = %d ans = %d\n", k, ans);
    }
    return ans;
}

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
    /*forn(iter, 10000) {
        int n = rand() % 1000 + 1;
        mod = rand() % 100 + 1;
        printf("n = %d mod = %d\n", n, mod);
        assert(ez_sol(n) == get(n));
    }*/
    /*fore(n, 1, 1000)
        for(mod = 1; mod <= 20; ++mod) {
            printf("n = %d mod = %d\n", n, mod);
            assert(ez_sol(n) == get(n));
        }*/
    forn(test, tests) {
        int n;
        scanf("%d%d", &n, &mod);
        int ans = get(n);
        /*int right_ans = ez_sol(n);
        printf("right_ans = %d\n", right_ans);
        assert(ans == right_ans);*/
        printf("%d\n", ans);
    }
}

