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

const int maxn = 105;

int ans[maxn][maxn];
int n, a, b;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    int cur_even = 2;
    int cur_odd = 1;
    forn(i, a)
    {
        forn(j, b)
        {
            int x = 0;
            if ((i + j) % 2 == 1)
            {
                if (cur_even <= n)
                {
                    x = cur_even;
                    cur_even += 2;
                }
            }
            else
            {
                if (cur_odd <= n)
                {
                    x = cur_odd;
                    cur_odd += 2;
                }
            }
            ans[i][j] = x;
        }
    }
    if (n != 1 && (cur_odd <= n || cur_even <= n))
    {
        printf("-1");
    }
    else
    {
        forn(i, a)
        {
            forn(j, b)
                printf("%d ", ans[i][j]);
            printf("\n");
        }
    }
}

