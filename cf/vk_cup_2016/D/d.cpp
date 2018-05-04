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

const int maxn = 2e5+5;

vector <pair<string, int > > commands;
int a[maxn];
vi pos_jump;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, s, d;
    scanf("%d%d%d%d", &n, &m, &s, &d);
    fore(j, 1, n)
        scanf("%d", &a[j]);
    sort(a + 1, a + n + 1);
    a[0] = -1;
    a[n + 1] = m + 1;
    fore(jump, 0, n - 1)
        if (a[jump + 1] - 1 - (a[jump] + 1) >= s)
        {
            pos_jump.pb(jump);
//            printf("pos_jump %d\n", jump);
        }
    int cur = n;
    int cur_jump = (int)pos_jump.size() - 1;
    while(true)
    {
        if (a[cur] + 1 != a[cur + 1] - 1)
            commands.pb(mp("RUN", a[cur + 1] - 1 - (a[cur] + 1)));
        if (cur == 0)
            break;
        int nnew = -1;
        while (cur_jump >= 0 && pos_jump[cur_jump] >= cur)
            cur_jump--;
        while(cur_jump >= 0)
        {
            int jump = pos_jump[cur_jump];
            if (a[cur] + 1 - (a[jump + 1] - 1) <= d)
            {
                nnew = jump;
                cur_jump--;
            }
            else break;
        }
        if (nnew == -1)
        {
            printf("IMPOSSIBLE");
            exit(0);
        }
        commands.pb(mp("JUMP", a[cur] + 1 - (a[nnew + 1] - 1)));
        cur = nnew;
    }
    for (int j = (int)commands.size() - 1; j >= 0; j--)
        cout << commands[j].fi << " " << commands[j].se << endl;
    
    
}
