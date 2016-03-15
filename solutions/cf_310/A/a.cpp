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

int a[maxn];
int n, k;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    int answer = 0;
    int parts = 0;
    forn(j, k)
    {
        int total;
        scanf("%d", &total);
        forn(j, total)
        {
            scanf("%d", &a[j]);
        }
        if (a[0] == 1)
        {
            parts++;
            for (int i = 1; i < total; i++)
                if (a[i] != a[i - 1] + 1)
                {
                    parts += total - i;
                    answer += total - i;
                    break;
                }
        }
        else
        {
            parts += total;
            answer += total - 1;
        }
    }
    answer += parts - 1;
    printf("%d", answer);
}
