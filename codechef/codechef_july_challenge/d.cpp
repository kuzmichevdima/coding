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

int start[maxn];
int want[maxn];
int penalty[maxn];
vector <pii> to_add[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n, d;
        scanf("%d%d", &n, &d);
        i64 answer = 0;
        set<pii> order;
        fore(day, 1, d)
            to_add[day].clear();
        forn(i, n) {
            scanf("%d%d%d", &start[i], &want[i], &penalty[i]);
            answer += (i64)penalty[i] * want[i];
            to_add[start[i]].pb(mp(penalty[i], i));
        }
        fore(day, 1, d) {
            for (pii p : to_add[day]) {
                order.insert(p);
                //printf("add (%d %d)\n", p.fi, p.se);
            }
            if (!order.empty()) {
                pii fr = *order.rbegin();
             //   printf("front %d %d\n", fr.fi, fr.se);
                order.erase(fr);
                int num = fr.second;
                want[num]--;
                answer -= penalty[num];
                if (want[num] > 0)
                    order.insert(fr);
            }
        }
        cout << answer << endl;
    }
}

