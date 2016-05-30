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

struct Treap {
    Treap * l, *r;
    int val, y, sz;
    Treap(int x) {
        l = r = NULL;
        val = x;
        y = rand();
        sz = 1;
    }
};

const int maxn = 2e6+5;

int ans[maxn];

typedef Treap * Pt;

inline int get_size(Pt & p) {
    return p == NULL ? 0 : p->sz;
}

inline void recalc(Pt & p) {
    if (p != NULL) {
         p->sz = get_size(p->l) + get_size(p->r) + 1;
    }
}

void merge(Pt & T, Pt L, Pt R) {
    if (L == NULL) {
        T = R;
        return;
    }
    if (R == NULL) {
        T = L;
        return;
    }
    if (R->y > L->y) {
        T = R;
        merge(T->l, L, T->l);
    } else {
        T = L;
        merge(T->r, T->r, R);
    }
    recalc(T);
}

void split(Pt T, int x0, Pt & L, Pt & R) {
    if (T == NULL) {
        L = R = NULL;
        return;
    }
    if (get_size(T->l) >= x0) {
        R = T;
        split(T->l, x0, L, R->l);
        recalc(R);
    } else {
        L = T;
        split(T->r, x0 - get_size(T->l) - 1, L->r, R);
        recalc(L);
    }
}

inline void shift(Pt & root, int cnt) {
    if (cnt != 0) {
        Pt lp, rp;
        split(root, get_size(root) - cnt, lp, rp);
        merge(root, rp, lp);
    }
}

int pos, n, q;
Pt even = NULL;
Pt odd = NULL;

void go(Pt cur) {
    if (cur == NULL)
        return;
    go(cur->l);
    ans[pos] = cur->val;
    pos += 2;
    go(cur->r);
}

void print_all() {
    pos = 0;
    go(even);
    pos = 1;
    go(odd);
    forn(j, n)
        printf("%d ", ans[j] + 1);
    printf("\n");
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int starttime = clock();
    scanf("%d%d", &n, &q);
    forn(i, n) {
        Pt nnew = new Treap(i);
        Pt tmp;
        if (i % 2 == 0) {
            merge(tmp, even, nnew);
            even = tmp;
        } else {
            merge(tmp, odd, nnew);
            odd = tmp;
        }
    }
    forn(i, q) {
        int typ;
        scanf("%d", &typ);
        if (typ == 1) {
            int x;
            scanf("%d", &x);
            if (x < 0)
                x = n + x;
            if (x % 2 == 0) {
                shift(odd, x / 2);
                shift(even, x / 2);
            } else {
                shift(odd, x / 2 + 1);
                shift(even, x / 2);
                swap(odd, even);
            }
        } else {
            swap(odd, even);
        }
       // print_all();
    }
    print_all();
}
