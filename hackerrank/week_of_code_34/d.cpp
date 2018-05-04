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

const int mod = 1e9+7;
const int maxn = 2e5+5;
const int maxF = 1e5;

i64 ans;
i64 A[maxn];
i64 B[maxn];
i64 deltaA[maxn];
i64 deltaB[maxn];
int F[maxF + 5];
int c[maxn];
vi edges[maxn];

inline void addmod(i64& x, i64 y) {
    x = (y + x) % mod;
}

void dfs(int v, int anc) {
    i64 f_cv = F[c[v]];
    i64 f_cv1 = c[v] == 0 ? 0 : F[c[v] - 1];
    i64 f_cv2 = c[v] <= 1 ? 0 : F[c[v] - 2];
    i64 sum_A = 0, sum_B = 0;
    for (int u : edges[v]) {
        if (u == anc)
            continue;
        dfs(u, v);
        deltaA[u] = (A[u] * f_cv + B[u] * f_cv1) % mod;
        deltaB[u] = c[v] == 0 ? B[u] : (A[u] * f_cv1 + B[u] * f_cv2) % mod;
        //printf("deltaA[%d] = %lld deltaB[%d] = %lld\n", u, deltaA[u], u, deltaB[u]);
        addmod(A[v], deltaA[u]);
        addmod(B[v], deltaB[u]);
        addmod(sum_A, A[u]);
        addmod(sum_B, B[u]);
        i64 tmp = deltaA[u] * A[u] + deltaB[u] * B[u];
        addmod(ans, mod - tmp % mod);
    }
    addmod(ans, A[v] * sum_A + B[v] * sum_B);
    addmod(ans, 2 * A[v] + f_cv);
    addmod(A[v], f_cv);
    addmod(B[v], f_cv1);
    //printf("A[%d] = %lld B[%d] = %lld ans = %lld\n", v, A[v], v, B[v], ans);
}

void precalc() {
    F[0] = F[1] = 1;
    fore(j, 2, maxF)
        F[j] = (F[j - 1] + F[j - 2]) % mod;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    precalc();
    int n;
    scanf("%d", &n);
    forn(i, n - 1) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    fore(j, 1, n)
        scanf("%d", &c[j]);
    dfs(1, -1);
    cout << ans;
}

