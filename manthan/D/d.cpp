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

const int maxn = 1005;

int n;

int counter[maxn];
int cur[maxn];
int p[maxn][maxn];
int a[maxn];
int L[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    vi list;
    scanf("%d", &n);
    forn(i, n)
    {
        scanf("%d", &a[i]);
        list.pb(a[i]);
    }
    sort(list.begin(), list.end());
    list.resize(unique(list.begin(), list.end()) - list.begin());
    forn(i, n)
    {
        int t = lower_bound(list.begin(), list.end(), a[i]) - list.begin();
        //ind[i] = t;
        counter[t]++;
    }
    forn(i, list.size())
    {
        forn(j, list.size())
        {
            int x = list[i] + list[j];
            int t = lower_bound(list.begin(), list.end(), x) - list.begin();
            if (t != (int)list.size() && list[t] == x)
            {
                p[i][j] = t;
            }
            else p[i][j] = -1;
        }
    }
//    for (int x : list)
   //     printf("%d ", x);
    int ans = 0;
    forn(i, list.size())
        forn(j, list.size()) if (i != j || counter[i] > 1)
        {
            int code = i * n + j + 1;
            int x = i;
            cur[x] = code;
            L[x] = counter[x] - 1;
            int y = j;
            cur[y] = code;
            if (x == y)
                L[y]--;
            else L[y] = counter[y] - 1;
            int len = 2;
            while(true)
            {
                int z = p[x][y];
                //printf("x = %d y = %d z = %d\n", x, y, z);
                if (z == -1)
                    break;
                if (cur[z] != code)
                {
                    cur[z] = code;
                    L[z] = counter[z] - 1;
                }
                else
                {
                    if (L[z] == 0)
                        break;
                    L[z]--;
                }
                x = y;
                y = z;
                len++;
            }
            ans = max(ans, len);
        }
    printf("%d", ans);
}
