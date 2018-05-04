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

const int inf = 2e9;
vi lifts;
vi lads;

int use(int x1, int y1, int x2, int y2, int pos, int s) {
    int res = abs(y1 - pos) + abs(y2 - pos);
    int deltax = abs(x1 - x2);
    res += deltax / s;
    if (deltax % s != 0)
        res++;
    return res;
}

int speed;

int get(int x1, int y1, int x2, int y2) {
    int res = x1 == x2 ? abs(y1 - y2) : inf;
    int pos = lower_bound(lads.begin(), lads.end(), y1) - lads.begin();
    if (pos <  (int)lads.size())
        res = min(res, use(x1, y1, x2, y2, lads[pos], 1));
    pos--;
    if (pos >= 0)
        res = min(res, use(x1, y1, x2, y2, lads[pos], 1));
    
    pos = lower_bound(lifts.begin(), lifts.end(), y1) - lifts.begin();
    if (pos < (int)lifts.size())
        res = min(res, use(x1, y1, x2, y2, lifts[pos], speed));
    pos--;
    if (pos >= 0)
        res = min(res, use(x1, y1, x2, y2, lifts[pos], speed));
    return res;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int floors, len, lad_num, lift_num;
    scanf("%d%d", &floors, &len);
    scanf("%d%d%d", &lad_num, &lift_num, &speed);
    lads.resize(lad_num);
    forn(i, lad_num)
        scanf("%d", &lads[i]);
    lifts.resize(lift_num);
    forn(i, lift_num)
        scanf("%d", &lifts[i]);
    int Q;
    scanf("%d", &Q);
    forn(q, Q) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int first = get(x1, y1, x2, y2);
        int second = get(x2, y2, x1, y1);
        int ans = min(first, second);
        printf("%d\n", ans);
    }
        
}

