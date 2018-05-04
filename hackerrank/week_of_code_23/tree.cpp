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

i64 A[maxn];
i64 B[maxn];
i64 C[maxn];
i64 sumA[maxn];
int jump[maxn][17];
int h[maxn];
vi edges[maxn];
i64 sumC[maxn];
i64 D[maxn];

int get_lca(int u, int v) {
    if (h[u] < h[v])
        swap(u, v);
    int diff = h[u] - h[v];
    forn(j, 17)
        if (diff & (1 << j)) {
            u = jump[u][j];
        }
    if (u == v)
        return u;
    for (int j = 16; j >= 0; j--) {
        if (jump[u][j] != 0 && jump[v][j] != 0 && jump[u][j] != jump[v][j]) {
            u = jump[u][j];
            v = jump[v][j];
        }
    }
    
    return jump[u][0];
}

void dfs(int v) {
    C[v] = 1;
    fore(j, 1, 16) {
        jump[v][j] = jump[jump[v][j - 1]][j - 1];
        if (jump[v][j] == 0)
            break;
    }

    for (int u : edges[v]) {
        h[u] = h[v] + 1;
        jump[u][0] = v;
        dfs(u);
        C[v] += C[u];
        A[v] += A[u] + C[u];
        B[v] += B[u] + 2 * A[u] + C[u];
    }
}

int get_d(int v, int u) {
    return h[v] + h[u] - 2 * h[get_lca(v, u)];
}

void calc(int v) {
    for (int u : edges[v]) {
        sumA[u] = sumA[v] + A[u];
        sumC[u] = sumC[v] + C[u];
        D[u] = D[v] + C[u] + sumC[v];
        calc(u);
    }
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
    fore(j, 2, n) {
        int x;
        scanf("%d", &x);
        //x = rand() % (j - 1) + 1;
        edges[x].pb(j);
    }
    dfs(1);
    sumA[1] = A[1];
    sumC[1] = D[1] = C[1];
    calc(1);
    /*fore(v, 1, n) {
        printf("v = %d anc = %d h = %d A = %lld B = %lld C = %lld sumC = %lld D = %lld\n", v, jump[v][0], h[v], A[v], B[v], C[v], sumC[v], D[v]);
    }*/

    int Q;
    scanf("%d", &Q);
    /*fore(w, 1, n)
        fore(v, 1, n) {
            int u = w;*/
    forn(q, Q) { 
        int u, v;
        scanf("%d%d", &u, &v);
        int lca = get_lca(u, v);
  //      printf("u = %d v = %d lca = %d\n", u, v, lca);
        i64 ans;
        if (lca == v) {
            /*i64 tmp = 0;
            fore(j, 1, n) if (get_lca(j, v) == v) {
                int d = get_d(u, j);
                tmp += (i64)d * d;
            }*/

            i64 d = h[u] - h[v];
            ans = B[v] + (-4) * (sumA[u] - sumA[v]) + A[v] * 2 * d;
            i64 supersum = D[u] - D[v] - sumC[v] * d;
//            cout << "supersum = " << supersum << endl;
            ans += d * d * C[v] - supersum * 4;

            //cout << "tmp = " << tmp << " ans = " << ans << endl; 
            //assert(tmp == ans);
        } else {
            i64 d = h[u] - 2 * h[lca] + h[v];
            ans = d * d * C[v] + 2 * d * A[v] + B[v];
        }
        cout << ans << endl;
    }
}

