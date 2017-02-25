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

int a[maxn];
vi list[maxn];
vi edges[maxn];

void undo_changes(set <int> & changes) {
    for (int x : changes)
        a[x] = 1 - a[x];
}

bool change(int pointer, int num) {
    //printf("change %d %d\n", pointer, num);
    set <int> used_conn;
    set <pii> to_change;
    set <int> changes;
    to_change.insert(mp(pointer, num));
    while(!to_change.empty()) {
        pii p = *to_change.begin();
        to_change.erase(to_change.begin());
        if (a[p.fi] != 0)
            continue;
        int conn_num = edges[p.fi][p.se];
        //printf("p = %d %d gonna use %d\n", p.fi, p.se, conn_num);
        if (used_conn.find(conn_num) != used_conn.end()) {
            undo_changes(changes);
            return false;
        }
        used_conn.insert(conn_num);
        for (int x : list[conn_num]) {
            if (changes.find(x) == changes.end())
                changes.insert(x);
            else changes.erase(x);
            a[x] = 1 - a[x];
            if (a[x] == 0) 
                to_change.insert(mp(x, edges[x][0] == conn_num ? 1 : 0));
        }
    }
    return true;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    fore(j, 1, n)
        scanf("%d", &a[j]);
    forn(i, m) {
        int sz;
        scanf("%d", &sz);
        forn(j, sz) {
            int x;
            scanf("%d", &x);
            list[i].pb(x);
            edges[x].pb(i);
        }
    }
    fore(pointer, 1, n) {
        if (a[pointer] == 0) {
            bool flag = change(pointer, 0);
            if (!flag) {
                flag = change(pointer, 1);
                if (!flag) {
                    printf("NO");
                    exit(0);
                }
            }
        }
    }
    printf("YES");
}
