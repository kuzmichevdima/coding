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

const int maxn = 150005;

vector <int> edges[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(j, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[x].pb(y);
        edges[y].pb(x);
    }
    fore(j, 1, n)
        sort(edges[j].begin(), edges[j].end());
    fore(y, 1, n) {
        forn(i, edges[y].size()) {
            int x = edges[y][i];
            int start = 0;
            fore(j, i + 1, (int)edges[y].size() - 1) {
                int z = edges[y][j];
                auto iter = lower_bound(edges[x].begin() + start, edges[x].end(), z);
                if (iter == edges[x].end() || *iter != z) {
                    printf("NO");
                    exit(0);
                }
                start = iter - edges[x].begin() + 1;
            }
        }
    }
    printf("YES");
//    printf("\ntime %d\n", (int)clock() - start_time);
}
