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

struct Edge {
    int fr, to, w;
};

struct Query {
    int fr, to, w, idx;
};

bool operator < (Query first, Query second) {
    return first.w < second.w;
}
const int maxn = 2e5+5;

Query queries[maxn];
vi list;
int tree[maxn * 4];
vector <pii> edges[maxn];
int f[maxn];
int answer[maxn];
vi list_w;

void dfs(int v, int anc=-1) {
    list.pb(v);
    for (pii e : edges[v]) {
        int u = e.fi;
        if (u == anc)
            continue;
        dfs(u, v);
        list.pb(v);
    }
}

int get(int i, int L, int R, int A, int B) {
    if (A >= R || L >= B)
        return 0;
    if (L == A && R == B)
        return tree[i];
    int M = (L + R) / 2;
    return get(i * 2, L, M, A, min(M, B)) ^ get(i * 2 + 1, M, R, max(A, M), B);
}

void upd(int i, int L, int R, int pos) {
    if (L + 1 == R) {
        tree[i] = list_w[pos];
        return;
    }
    int M = (L + R) / 2;
    if (pos < M)
        upd(i * 2, L, M, pos);
    else upd(i * 2 + 1, M, R, pos);
    tree[i] = tree[i * 2] ^ tree[i * 2 + 1];
}

void upd(int edge_idx) {
    //printf("upd pos %d val = %d\n", edge_idx, list_w[edge_idx]);
    upd(1, 0, (int)list.size(), edge_idx);
}

int get(int fr, int to) {
    int start = min(f[fr], f[to]);
    int finish = max(f[fr], f[to]);
    //printf("get fr = %d to = %d [%d;%d)\n", fr, to, start, finish);
    return get(1, 0, (int)list.size(), start, finish);
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
        int n;
        scanf("%d", &n);
        fore(j, 1, n)
            edges[j].clear();
        list.clear();
        map <pii, int> M;
        forn(j, n - 1) {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            M[mp(min(x,y), max(x, y))] = w;
            edges[x].pb(mp(y, w));
            edges[y].pb(mp(x, w));
        }
        dfs(1);
        list_w.clear();
        forn(j, (int)list.size() - 1) {
            int x = list[j];
            int y = list[j + 1];
            list_w.pb(M[mp(min(x, y), max(x, y))]);
        }
        /*for (int x : list)
            printf("%d ", x);
        printf("\n");
        for (int x : list_w)
            printf("%d ", x);
        printf("\n");*/
        fore(j, 1, n)
            f[j] = -1;
        forn(i, list.size()) {
            if (f[list[i]] == -1)
                f[list[i]] = i;
            if (f[list[i]] == -1)
                f[list[i]] = i;
        }
        vector <pii> order;
        forn(idx, list_w.size())
            order.pb(mp(list_w[idx], idx));
        sort(order.begin(), order.end());
        int m;
        scanf("%d", &m);
        forn(q, m) {
            scanf("%d%d%d", &queries[q].fr, &queries[q].to, &queries[q].w);
            queries[q].idx = q;
        }
        sort(queries, queries + m);
        int pointer = 0;
        memset(tree, 0, sizeof(tree));
        forn(q, m) {
            while (pointer < (int)list_w.size() && order[pointer].fi <= queries[q].w) {
                upd(order[pointer].se);
                pointer++;
            }
            //printf("query w = %d fr = %d to = %d pointer = %d\n", queries[q].w, queries[q].fr, queries[q].to, pointer);
            //if (f[queries[q].fr] > f[queries[q].to])
              //  swap(queries[q].fr, queries[q].to);
            answer[queries[q].idx] = get(queries[q].fr, queries[q].to);
            //printf("answer: %d\n", answer[queries[q].idx]);
        }
        forn(q, m)
            printf("%d\n", answer[q]);
    }

}

