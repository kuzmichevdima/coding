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

int n, m, k;

typedef int myarr[maxn];
myarr miny, maxy, minz, maxz;
int sparse[4][18][maxn];
int prec[maxn];

int get_min(int number, int start, int len) {
    return min(sparse[number][prec[len]][start], sparse[number][prec[len]][start + len - (1 << prec[len])]);
}

int get_max(int number, int start, int len) {
    return max(sparse[number][prec[len]][start], sparse[number][prec[len]][start + len - (1 << prec[len])]);
}

void build(myarr& arr, int number, bool is_min) {
    forn(j, n)
        sparse[number][0][j] = arr[j];
    fore(level, 1, 17)
        fore(j, 0, n - (1 << level)) {
            int t1 = sparse[number][level - 1][j];
            int t2 = sparse[number][level - 1][j + (1 << (level - 1))];
            sparse[number][level][j] = is_min ?  min(t1, t2) : max(t1, t2);
        }
}


bool can(int sz) {
    fore(start, 0, n - sz) {
        //printf("start = %d y1 = %d y2 = %d z1 = %d z2 = %d\n", start, y1, y2, z1, z2);
        int ymin = get_max(0, start, sz);
        int ymax = get_min(1, start, sz);
        int zmin = get_max(2, start, sz);
        int zmax = get_min(3, start, sz);
        if (ymax - ymin + 1 >= sz && zmax - zmin + 1 >= sz)
            return true;
        
    }
    return false;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    int p, q;
    scanf("%d%d", &p, &q);
    i64 total_free = 0;
    forn(i, n) {
        scanf("%d%d%d%d", &miny[i], &minz[i], &maxy[i], &maxz[i]);
        total_free += (i64)(maxy[i] - miny[i] + 1) * (maxz[i] - minz[i] + 1);
    }
    build(miny, 0, false);
    build(maxy, 1, true);
    build(minz, 2, false);
    build(maxz, 3, true);
    prec[1] = 0;
    fore(j, 2, n + 1) {
        prec[j] = prec[j / 2] + 1;
        //printf("prec[%d] = %d\n", j, prec[j]);
    }
    //cout << total_free << endl;
    //can(2);
    //exit(0);
    int start = 0;
    int finish = n;
    while(start < finish) {
        int middle = (start + finish) / 2 + 1;
        if (can(middle))
            start = middle;
        else finish = middle - 1;
    }
    //printf("max size is %d\n", start);
    i64 ans = 0;
    fore(maxx, 1, start) {
        i64 nnew = (i64)maxx * p + (total_free - (i64)maxx * maxx * maxx + 1) * q;
        //cout << maxx << " " << nnew << endl;
        ans = max(ans, nnew);
    }
    cout << ans;
}

