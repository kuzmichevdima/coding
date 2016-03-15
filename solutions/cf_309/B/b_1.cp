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

const int maxn = 100;

int p[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    forn(j, n)
        p[j] = j + 1;
    do
    {
        vector <vi> cycles;
        vector <bool> was(n, false);
        forn(j, n) if (!was[j])
        {
            int cur = j;
            vi nnew(1);
            nnew[0] = p[j];
            was[j] = true;
            while(p[cur] != j + 1)
            {
                cur = p[cur] - 1;   
                was[cur] = true;
                nnew.pb(p[cur]);
            }
            int max_pos = 0;
            fore(j, 1, nnew.size() - 1)
                if (nnew[j] > nnew[max_pos])
                    max_pos = j;
            vi nnew1;
            fore(j, max_pos, nnew.size() - 1)
                nnew1.pb(nnew[j]);
            forn(j, max_pos)
                nnew1.pb(nnew[j]);
            cycles.pb(nnew1);
        }
        sort(cycles.begin(), cycles.end());
        vi new_v;
        for (auto x : cycles)
            for (int y : x)
                new_v.pb(y);
        assert((int)new_v.size() == n);
        bool fail = false;
        forn(j, n)
            if (new_v[j] != p[j])
            {
                fail = true;
                break;
            }
        if (!fail)
        {
            forn(j, n)
                printf("%d ", p[j]);
            printf("\n");
        }
    }
    while(next_permutation(p, p + n));
}
