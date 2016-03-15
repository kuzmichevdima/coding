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

const int max_x = 1e6+5;
const int maxn = 1005;

bool found;
int k, j, n;

bool mark[max_x];
int a[maxn][6];

void go(int cur, int pos, int changed)
{
    if (found)
        return;
    if (pos == 6)
    {
        if (mark[cur])
        {
            //printf("k = %d found %d\n", k, cur);
            found = true;
        }
        else mark[cur] = true;
        return;
    }
    if (changed < k)
    {
        fore(digit, 0, 9)
            go(cur * 10 + digit, pos + 1, changed + (digit != a[j][pos]));
    }
    else go(cur * 10 + a[j][pos], pos + 1, changed);
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
    forn(j, n)
    {
        int x;
        scanf("%d", &x);
        for (int pos = 5; pos >= 0; pos--)
        {
            a[j][pos] = x % 10;
            x /= 10;
        }
    }
    for (k = 1; k <= 6; k++)
    {
        memset(mark, false, sizeof(mark));
        found = false;
        for (j = 0; j < n; j++)
            go(0, 0, 0);
        if (found)
        {
            printf("%d", k - 1);
            exit(0);
        }
    }
    printf("6");
}
