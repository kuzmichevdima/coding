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

struct Elem {
    i64 x, y, sz;
    Elem* L, *R;
    Elem(i64 x) : x(x), y(rand()), sz(1), L(NULL), R(NULL) {}
};
typedef Elem* pt;

inline int get_size(pt p) {
    return p == NULL ? 0 : p->sz;
}

void recalc(pt& p) {
    if (p == NULL)
        return;
    p->sz = get_size(p->L) + get_size(p->R) +  1;
}

void merge(pt& p, pt L, pt R) {
    if (L == NULL) {
        p = R;
        return;
    }
    if (R == NULL) {
        p = L;
        return;
    }
    if (L->y > R->y) {
        p = L;
        merge(p->R, p->R, R);
    } else {
        p = R;
        merge(p->L, L, p->L);
    }
    recalc(p);
}

void split(pt p, i64 x0, pt& L, pt& R) {
    if (p == NULL) {
        L = R = NULL;
        return;
    }
    if (x0 >= p->x) {
        L = p;
        split(p->R, x0, L->R, R);
        recalc(L);
    }
    else {
        R = p;
        split(p->L, x0, L, R->L);
        recalc(R);
    }
    
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, d;
    scanf("%d%d", &n, &d);
    pt root = NULL;
    forn(j, n) {
        int x;
        scanf("%d", &x);
        pt lower, upper;
        split(root, x, lower, upper);
        printf("split done\n");
        pt tmp;
        merge(tmp, lower, new Elem(x));
        printf("first merge\n");
        merge(root, tmp, upper);
        printf("second merge\n");
    }
    //printf("size is %d\n", get_size(root));
    assert(get_size(root) == n);
    int ans = 0;
    i64 delta = 0; 
    forn(iter, 2 * n + 5) {
        split(root, D - delta, lower, upper);
        ans = max(ans, get_size(lower));
        merge(root, lower, upper);
        if (root->R == NULL) {
            
        }
    }
    printf("%d", ans);
}

