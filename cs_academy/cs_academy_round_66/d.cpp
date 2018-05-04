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

const int maxn = 1e3 + 5;

bool edge[maxn][maxn];
int n;
bool used[maxn];
int p_left[maxn];
int p_right[maxn];
int a[maxn][maxn];

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    forn(i, n)
        if (edge[v][i]) {
            if (p_right[i] == -1 || dfs(p_right[i])) {
                p_left[v] = i;
                p_right[i] = v;
                return true;
            }
        }
    return false;
}

void trying(char ch) {
    /*printf("trying\n");
    forn(i, n) {
        forn(j, n)
            printf("%d ", edge[i][j]);
        printf("\n");
    }*/
    forn(i, n)
        p_left[i] = p_right[i] = -1;
    forn(i, n) {
        memset(used, false, sizeof(used));
        if (p_left[i] == -1) {
            dfs(i);
        }
    }
    forn(i, n) {
        if (p_left[i] == -1)
            return;
    }
    vi perm(n);
    vi wher(n);
    forn(i, n)
        perm[i] = wher[i] = i;
    forn(i, n) {
        if (wher[i] != p_left[i]) {
            printf("%c %d %d\n", ch, wher[i] + 1, p_left[i] + 1);
            int p1 = wher[i];
            int p2 = p_left[i];
            swap(perm[p1], perm[p2]);
            wher[perm[p1]] = p1;
            wher[perm[p2]] = p2;
        }
    }
    exit(0);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    forn(i, n)
        forn(j, n)
            scanf("%d", &a[i][j]);
    forn(i, n)
        forn(j, n)
            edge[i][j] = (a[i][j] == 1);
    trying('R');
    forn(i, n)
        forn(j, n)
            edge[i][j] = (a[j][i] == 1);
    trying('C');
    printf("-1");
}

