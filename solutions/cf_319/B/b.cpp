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

int p[maxn];
int n;
bool used[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    fore(j, 1, n)
        scanf("%d", &p[j]);
    fore(j, 1, n)
        if (p[j] == j)
        {
            printf("YES\n");
            fore(h, 1, n) if (h != j)
                printf("%d %d\n", j, h);
            exit(0);
        }
    int first = -1, second = -1;
    fore(j, 1, n)
        if (p[p[j]] == j)
        {
            first = j;
            second = p[j];
            break;
        }
    if (first == -1)
    {
        printf("NO");
        exit(0);
    }
    used[first] = used[second] = true;
    vector <pii> ans;
    ans.pb(mp(first, second));
    fore(j, 1, n) if (!used[j])
    {
        int cur = j;
        vi cycle;
        while(true)
        {
            used[cur] = true;
            cycle.pb(cur);
            cur = p[cur];
            if (cur == j)
                break;
        }
        if (cycle.size() % 2 == 1)
        {
            printf("NO");
            exit(0);
        }
        forn(j, cycle.size())
            if (j % 2 == 0)
                ans.pb(mp(first, cycle[j]));
            else ans.pb(mp(second, cycle[j]));
    }
    assert((int)ans.size() == n - 1);
    printf("YES\n");
    for (pii p : ans)
        printf("%d %d\n", p.fi, p.se);
}
