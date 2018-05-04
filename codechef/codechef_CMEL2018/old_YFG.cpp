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

const int maxn = 2e5+5;
const int LOG = 17;

vi edges[maxn];
int timer;
int tin[maxn];
int tout[maxn];
int h[maxn];
int jmp[maxn][LOG + 1];
i64 ans[maxn];
int cur_color;
vi q_nums[maxn];
int color[maxn];

void dfs(int v, int anc=-1) {
    h[v] = anc == -1 ? 0 : h[anc] + 1;
    jmp[v][0] = anc;
    fore(j, 1, LOG) {
        int x = jmp[v][j - 1];
        jmp[v][j] = x == -1 ? -1 : jmp[x][j - 1];
    }
    tin[v] = timer++;
    for (int u : edges[v]) {
        if (u != anc)
            dfs(u, v);
    }
    tout[v] = timer++;
}

int up(int v, int delta) {
    int res = v;
    forn(bit, LOG + 1)
        if (delta & (1 << bit))
            res = jmp[res][bit];
    return res;
}

bool is_anc(int x, int y) {
    return tin[x] < tin[y] && tout[x] > tout[y];
}

int count_dfs(int v, int anc, int top) {
    int sum = 0;
    //bool v_is_colored = (color[v] == cur_color || !q_nums[v].empty());
    bool v_is_colored = color[v] == cur_color;
    int new_top = top + v_is_colored;
    i64 part = 0;
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        int cur = count_dfs(u, v, new_top);
        part += (i64)cur * sum;
        sum += cur;
    }
    i64 v_ans = part * 2 * top;
    for (int q : q_nums[v]) {
        ans[q] = v_ans;
    }
    q_nums[v].clear();
    return sum + v_is_colored; 
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
    forn(test, tests) {
        int n, q;
        scanf("%d%d", &n, &q);
        map<int, vi> vertex_with_color;
        fore(i, 1, n) {
            scanf("%d", &color[i]);
            //scanf("%d", &color[i]);
            vertex_with_color[color[i]].pb(i);
        }
        fore(i, 1, n)
            edges[i].clear();
        forn(i, n - 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            edges[x].pb(y);
            edges[y].pb(x);
        }
        dfs(1);
        map<int, vector<pii> > queries;
        forn(query, q) {
            int vert, c;
            scanf("%d%d", &vert, &c);
            queries[c].pb({vert, query});
        }
        for (auto iter : queries) {
            int c = iter.fi;
            bool flag = (i64)iter.se.size() * vertex_with_color[c].size() * LOG < (unsigned i64)n;
            //bool flag = false;
            if (flag) {
                for (pii p : iter.se) {
                    int center = p.fi;
                    int cnt_uppers = 0;
                    map<int, int> sons_cnt;
                    for (int v : vertex_with_color[c]) {
                        if (v == center)
                            continue;
                        if (is_anc(v, center)) {
                            cnt_uppers++;
                        }
                        else if (is_anc(center, v)) {
                            sons_cnt[up(v, h[v] - h[center] - 1)]++; 
                        }
                    }
                    int sum = 0;
                    i64 part = 0;
                    for (auto sons_iter : sons_cnt) {
                        //cout << "son " << sons_iter.fi << " " << sons_iter.se << endl;
                        part += (i64)sum * sons_iter.se;
                        sum += sons_iter.se;
                    }
                    ans[p.se] = part * 2 * cnt_uppers;
                }
            } else {
                cur_color = c;
                for (pii p : iter.se) {
                    q_nums[p.fi].pb(p.se);
                }
                count_dfs(1, -1, 0); 
            }
        }
        forn(j, q)
            cout << ans[j] << endl;
    }
}

