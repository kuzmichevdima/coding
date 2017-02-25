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

set <int> edges[maxn];
set <int> bamb[maxn];

void print_ans(int edge_len) {
//    printf("print ans %d\n", edge_len);
    while(edge_len % 2 == 0)
        edge_len /= 2;
    printf("%d", edge_len);
    exit(0);
}

void del_edge(int v, int u) {
    edges[v].erase(u);
    edges[u].erase(v);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    forn(j, n - 1) {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[u].insert(v);
        edges[v].insert(u);
    }
    set <int> order;
    fore(j, 1, n) if (edges[j].size() == 1) {
        order.insert(j);
        bamb[j].insert(0);
    }
    while(!order.empty()) {
        int v = *order.begin();
        order.erase(order.begin());
   //     printf("v = %d\n", v);
        if (bamb[v].size() == 1) {
            int bamb_len = *bamb[v].begin();
 //           printf("only 1 bamb %d\n", bamb_len);
            if (edges[v].empty()) {
                print_ans(bamb_len);
            }
            if (edges[v].size() == 1) {
                int u = *edges[v].begin(); 
                del_edge(v, u);
                bamb[u].insert(bamb_len + 1);
                order.insert(u);
            }
        } else if (bamb[v].size() == 2 && edges[v].empty()) {
            print_ans(*bamb[v].begin() + *bamb[v].rbegin());
        }
    }
    printf("-1");
}
