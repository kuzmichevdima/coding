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

const int maxn = 405;
const int inf = 1e9;

int a[maxn][maxn];
int n, m;

int bfs(int color)
{
    queue <int> Q;
    Q.push(1);
    vector <int> d(n + 1, inf);
    d[1] = 0;
    while(!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        fore(i, 1, n)
            if (a[v][i] == color && d[i] == inf)
            {
                d[i] = d[v] + 1;
                Q.push(i);
            }
    }
    return d[n];
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    forn(j, m)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        a[x][y] = a[y][x] = 1;
    }
    int L0 = bfs(0);
    int L1 = bfs(1);
    if (L0 == inf || L1 == inf)
    {
        cout << -1;
        exit(0);
    }
    int ans = max(L0, L1);
    printf("%d", ans);
}
