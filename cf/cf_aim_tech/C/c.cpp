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
const int inf = 1e9;

pii a[maxn];
int suff_miny[maxn];
int suff_maxy[maxn];
int pref_miny[maxn];
int pref_maxy[maxn];
int n;

i64 sqr(int x) {
    return (i64)x * x;
}

bool ok(int i, int j, i64 m) {
    return sqr(a[j].fi - a[i].fi) <= m && abs(a[j].fi) <= abs(a[i].fi);
}

bool semicheck(int s, int f, i64 m) {
    if (s == 0 && f == n - 1)
        return true;
    int prefminy = s == 0 ? inf : pref_miny[s - 1];
    int prefmaxy = s == 0 ? -inf : pref_maxy[s - 1]; 
    int suffminy = f == n - 1 ? inf : suff_miny[f + 1];
    int suffmaxy = f == n - 1 ? -inf : suff_maxy[f + 1];
    int miny = min(prefminy, suffminy);
    int maxy = max(prefmaxy, suffmaxy);
//    printf("maxy = %d miny = %d\n", maxy, miny);
    int maxabsx = max(abs(a[s].fi), abs(a[f].fi));
    return sqr(maxy - miny) <= m && sqr(maxabsx) + sqr(miny) <= m && sqr(maxabsx) + sqr(maxy) <= m;
}

bool check1(i64 m) {
    int pointer = 0;
    while(pointer + 1 < n && ok(0, pointer + 1, m))
        pointer++;
    forn(i, n) {
    //    printf("i = %d pointer = %d\n", i, pointer);
        if (a[i].fi > 0)
            break;
        if (semicheck(i, pointer, m))
            return true;
        if (pointer == i)
            pointer = i + 1;
        while(pointer + 1 < n && ok(i + 1, pointer + 1, m))
            pointer++;
        while(!ok(i + 1, pointer, m))
            pointer--;
    }
    return false;
}

bool check2(i64 m) {
    int pointer = n - 1;
    while(pointer - 1 >= 0 && ok(n - 1, pointer - 1, m))
        pointer--;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i].fi < 0)
            break;
        if (semicheck(pointer, i, m))
            return true;
        if (pointer == i)
            pointer = i - 1;
        while(pointer - 1 >= 0 && ok(i - 1, pointer - 1, m))
            pointer--;
        while(!ok(i - 1, pointer, m))
            pointer++;
    }
    return false;
}

void precalc() {
    pref_miny[0] = pref_maxy[0] = a[0].se;
    fore(i, 1, n - 1) {
        pref_miny[i] = min(pref_miny[i - 1], a[i].se);
        pref_maxy[i] = max(pref_maxy[i - 1], a[i].se);
    }
    suff_miny[n - 1] = suff_maxy[n - 1] = a[n - 1].se;
    for (int i = n - 2; i >= 0; i--) {
        suff_miny[i] = min(suff_miny[i + 1], a[i].se);
        suff_maxy[i] = max(suff_maxy[i + 1], a[i].se);
    }
}

bool check(i64 m) {
    return check1(m) || check2(m);
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
    forn(i, n) {
        scanf("%d%d", &a[i].fi, &a[i].se);
    }
    sort(a, a + n);
    precalc();
    i64 s = 0;
    i64 f = sqr(pref_maxy[n - 1] - pref_miny[n - 1]);
    while (s < f) {
       i64 m = (s + f) / 2;
       if (check(m))
           f = m;
       else s = m + 1;
    }
    cout << s;
    
}
