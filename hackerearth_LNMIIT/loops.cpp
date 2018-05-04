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
#include <stack>

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

vi ans;
//stack<int> st;
//int status[maxn];
vi edges[maxn];
vi rev_edges[maxn];
vi order;
bool mark[maxn];
vi lst;

/*void dfs(int v) {
    st.push(v);
    status[v] = 1;
    for (int u : edges[v]) {
        if (status[u] == 1) {
            vi new_loop;
            while(true) {
                int cur = st.top();
                st.pop();
                new_loop.pb(cur);
                if (cur == u)
                    break;
            }
            if (new_loop.size() > ans.size())
                ans = new_loop;
        }
    }
    for (int u : edges[v])
        if (status[u] == 0)
            dfs(u);
    status[v] = 2;
}*/

void dfs(int v) {
    mark[v] = true;
    for (int u : edges[v])
        if (!mark[u]) {
            dfs(u);
        }
    order.pb(v);
}

void paint(int v) {
    lst.pb(v);
    mark[v] = true;
    for (int u : rev_edges[v])
        if (!mark[u])
            paint(u);
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
    forn(j, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        rev_edges[y].pb(x);
    }
    fore(j, 1, n)
        if (!mark[j])
            dfs(j);
    reverse(order.begin(), order.end());
    memset(mark, false, sizeof(mark));
    for (int v : order)
        if (!mark[v]) {
            lst.clear();
            paint(v);
            if (lst.size() > ans.size())
                ans = lst;
        }
        /*reverse(ans.begin(), ans.end());
    int min_pos = 0;
    fore(j, 1, (int)ans.size() - 1)
        if (ans[j] < ans[min_pos])
            min_pos = j;
    fore(j, min_pos, (int)ans.size() - 1)
        printf("%d ", ans[j]);
    forn(j, min_pos)
        printf("%d ", ans[j]);*/
    sort(ans.begin(), ans.end());
    for (int x : ans)
        printf("%d ", x);
}

