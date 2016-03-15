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

const int maxn = 505;

bool a[maxn][maxn];
char answer[maxn];
int n, m;

void dfs(int v, int color)
{
    answer[v] = 'a' + color;
    fore(j, 1, n) if (a[v][j])
    {
        if (answer[j] == 0)
            dfs(j, 2 - color);
        else if (answer[j] != 'a' + 2 - color)
        {
            printf("No");
            exit(0);
        }
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
    scanf("%d%d", &n, &m);
    fore(i, 1, n)
        fore(j, 1, n) if (i != j)
            a[i][j] = true;
    forn(j, m)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        a[x][y] = a[y][x] = false;
    }
    fore(i, 1, n) if (answer[i] == 0)
    {
        bool flag = false;
        fore(j, 1, n) if (a[i][j])
        {
            flag = true;
            break;
        }
        if (flag)
            dfs(i, 0);
    }
    fore(i, 1, n) if (answer[i] == 0)
        answer[i] = 'b';
    fore(i, 1, n)
        fore(j, 1, n)
            if (!a[i][j] && abs(answer[i] - answer[j]) > 1)
            {
                printf("No\n");
                exit(0);
            }
    printf("Yes\n");
    fore(i, 1, n)
        printf("%c", answer[i]);
}
