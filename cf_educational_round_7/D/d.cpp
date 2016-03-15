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

const int n = 6;
int p1[n];
int p2[n];
vi list[n + 1];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    forn(i, n)
        p1[i] = i + 1;
    vi perm(2 * n), best_perm;
    int best = -1;
    do
    {
        forn(i, n)
            p2[i] = i + 1;
        do
        {
            fore(i, 1, n)
                list[i].clear();
            forn(i, n)
            {
                list[p1[i]].pb(2 * i);
                list[p2[i]].pb(2 * i + 1);
                perm[2 * i] = p1[i];
                perm[i * 2 + 1] = p2[i];
            }
            int cur = 0;
            fore(i, 1, n)
            {
                int d = list[i][1] - list[i][0];
                cur += (n - i) * abs(d + i - n);
            }
            if (best == -1 || cur < best)
            {
                best_perm = perm;
                best = cur;
            }
        }
        while(next_permutation(p2, p2 + n));
    }
    while(next_permutation(p1, p1 + n));
    printf("best = %d\n", best);
    for (int x : best_perm)
        printf("%d ", x);
}
