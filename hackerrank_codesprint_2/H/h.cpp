#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
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

const int maxn = 804;
const int dx[6] = {-1, -1, 0, 0, 1, 1};
const int dy[6] = {0, 1, -1, 1, 0, -1};

int mark[maxn][maxn];
int x_lower, y_lower, x_upper, y_upper, code;
char a[maxn][maxn];

void dfs(int x, int y) {
    mark[x][y] = code;
    forn(move, 6) {
        int newx = x + dx[move];
        int newy = y + dy[move];
        if (mark[newx][newy] != code && newx >= x_lower && newx <= x_upper &&
                newy >= y_lower && newy <= y_upper && a[x][y] == a[newx][newy])
            dfs(newx, newy);
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
    int n, m;
    scanf("%d%d\n", &n, &m);
    fore(i, 1, n) {
        fore(j, 1, m) {
            scanf("%c", &a[i][j]);
        }
        scanf("\n");
    }
    int tests;
    scanf("%d", &tests);
    code = 1;
    forn(test, tests) {
        scanf("%d%d%d%d", &x_lower, &y_lower, &x_upper, &y_upper);
        printf("%d %d %d %d\n", x_lower, y_lower, x_upper, y_upper);
        int prev_code = code;
        fore(i, x_lower, x_upper)
            fore(j, y_lower, y_upper)
                if (mark[i][j] != code) {
                    dfs(i, j);
                    code++;
                }
        printf("%d\n", code - prev_code);
    }
}
