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

const int maxn = 5e4+5;
const i64 inf = 2e18;

vi edges[maxn];
int c[maxn];
i64 sum[maxn];
int T;
int in[maxn];
int out[maxn];

void dfs(int v, int anc) {
    in[v] = T++;
    sum[v] = c[v];
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        dfs(u, v);
        sum[v] += sum[u];
    }
    out[v] = T++;
}

i64 ans;
int v;

map <i64, int> max_map, min_map;

inline void check(i64 need, bool flag, i64 fr, i64 to) {
  //  printf("check v = %d need = %lld flag = %d out[v] = %d\n", v, need, flag, out[v]);
    if (to - fr < 0)
        return;
    if (flag) {
        if (max_map.find(need) == max_map.end() || max_map[need] < out[v])
            return;
    }
    else {
        if (min_map.find(need) == min_map.end() || min_map[need] > out[v])
            return;
        //printf("min_map[need] = %d\n", min_map[need]);
    }
//    printf("updating %lld\n", to - fr);
    ans = min(ans, to - fr);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int q;
    scanf("%d", &q);
    forn(query, q) {
        min_map.clear();
        max_map.clear();
        int n;
        scanf("%d", &n);
        fore(i, 1, n) {
            scanf("%d", &c[i]);
            edges[i].clear();
        }
        forn(i, n - 1) {
            int u, v;
            scanf("%d%d", &v, &u);
            edges[u].pb(v);
            edges[v].pb(u);
        }
        T = 0;
        dfs(1, -1);
        i64 total = sum[1];
        vector <pii> vec;
        fore(i, 1, n)
            vec.pb(mp(in[i], i));
        sort(vec.begin(), vec.end());
        reverse(vec.begin(), vec.end());
        ans = inf;
        for (pii p : vec) {
            v = p.se;
            i64 s1 = sum[v];
            check(s1, true, total - 2 * s1, s1);
            check(total - 2 * s1, true, total - 2 * s1, s1);
            if ((total - s1) % 2 == 0)
                check((total - s1) / 2, true, s1, (total - s1) / 2);

            if (s1 % 2 == 0)
                check(s1 / 2, false, total - s1, s1 / 2);
            check(2 * s1 - total, false, 2 * s1 - total, total - s1);
            check(total - s1, false, s1 - (total - s1), total - s1);

            if (min_map.find(s1) == min_map.end())
                min_map[s1] = out[v];
            else min_map[s1] = min(min_map[s1], out[v]);

            if (max_map.find(s1) == max_map.end())
                max_map[s1] = out[v];
            else max_map[s1] = max(max_map[s1], out[v]);

        }
        /*        if (out[v] > out[u]) {
                    if (sum[u] * 2 == sum[v])
                        check(total - sum[v], sum[u], ans);
                    if (sum[u] == 2 * sum[v] - total)
                        check(sum[u], total - sum[v], ans);
                    if (sum[u] == total - sum[v])
                        check(sum[v] - sum[u], sum[u], ans);
                } else {
                    if (sum[u] == sum[v])
                        check(total - sum[u] - sum[v], sum[v], ans);
                    if (sum[v] == total - sum[v] - sum[u])
                        check(sum[u], sum[v], ans);
                    if (sum[u] == total - sum[v] - sum[u])
                        check(sum[v], sum[u], ans);
                }
            }*/
        if (ans == inf)
            ans = -1;
        cout << ans << endl;
    }
}
