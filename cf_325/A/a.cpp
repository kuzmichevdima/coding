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

const int maxn = 4005;

i64 p[maxn];
i64 v[maxn];
i64 d[maxn];
int n;

void run(int child)
{
    fore(j, child + 1, n - 1) if (p[j] >= 0)
    {
        p[j] -= d[child];
        if (p[j] < 0)
            run(j);
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
    scanf("%d", &n);
    forn(j, n)
    {
        cin >> v[j] >> d[j] >> p[j];
    }
    vi ans;
    forn(cur, n) if (p[cur] >= 0)
    {
        ans.pb(cur);
        i64 delta = v[cur];
        vi to_run;
        fore(child, cur + 1, n - 1)
            if (p[child] >= 0)
            {
                p[child] -= delta;
                if (p[child] < 0)
                    to_run.pb(child);
                delta--;
                if (delta == 0)
                    break;
            }
        forn(j, to_run.size())
            run(to_run[j]);
    }
    printf("%d\n", (int)ans.size());
    for (auto x : ans)
        printf("%d ", x + 1);
}
