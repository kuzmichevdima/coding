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

multiset<int> order[4][4];
int cost[maxn];
int first_c[maxn];
int second_c[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    forn(j, n)
        scanf("%d", &cost[j]);
    forn(j, n)
        scanf("%d", &first_c[j]);
    forn(j, n)
        scanf("%d", &second_c[j]);
    forn(j, n) {
        if (first_c[j] > second_c[j])
            swap(first_c[j], second_c[j]);
        order[first_c[j]][second_c[j]].insert(cost[j]);
    }
    int m;
    scanf("%d", &m);
    forn(j, m) {
        int fav;
        scanf("%d", &fav);
        int best = INT_MAX;
        int s, f;
        fore(first, 1, 3)
            fore(second, first, 3)
                if (first == fav || second == fav) {
                    if (!order[first][second].empty() && *order[first][second].begin() < best) {
                        best = *order[first][second].begin();
                        f = first;
                        s = second;
                    }
                }
        if (best == INT_MAX)
            printf("-1 ");
        else {
            printf("%d ", best);
            order[f][s].erase(order[f][s].begin());
        }
    }
}

