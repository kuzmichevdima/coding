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

struct Treap
{
    int x, sz, y;
    Treap * l, *r;
    Treap(int _x) : x(_x), sz(1), y(rand()), l(NULL), r(NULL) {}
};

typedef Treap * Pt;

inline int get_sz(Pt T)
{
    return(T == NULL ? 0 : T->sz);
}

inline void recalc(Pt & T)
{
    T->sz = get_sz(T->l) + get_sz(T->r) + 1;
}

Pt root_plus, root_minus;

void merge(Pt & T, Pt L, Pt R)
{
    if (L == NULL)
    {
        T = R;
        return;
    }
    if (R == NULL)
    {
        T = L;
        return;
    }
    if (L->y > R->y)
    {
        T = L;
        merge(T->r, T->r, R);
    }
    else
    {
        T = R;
        merge(T->l, L, T->l);
    }
    recalc(T);
}

void split(Pt T, int x0, Pt & L, Pt & R)
{
    if (T == NULL)
    {
        L = R = NULL;
        return;
    }
    if (T->x <= x0)
    {
        L = T;
        split(T->r, x0, L->r, R);
        recalc(L);
    }
    else
    {
        R = T;
        split(T->l, x0, L, R->l);
        recalc(R);
    }
}

inline void insert(Pt & root, int x0)
{
    Pt A, B, tmp;
    split(root, x0, A, B);
    Pt C = new Treap(x0);
    merge(tmp, A, C);
    merge(root, tmp, B);
}

inline void add_seg(int s, int f)
{
    insert(root_plus, s);
    insert(root_minus, f + 1);
}

inline int cnt(Pt & root, int p)
{
    Pt A, B;
    split(root, p, A, B);
    int res = get_sz(A);
    merge(root, A, B);
    return res;
}

inline int get(int p)
{
    int pluses = cnt(root_plus, p);
    int minuses = cnt(root_minus, p);
    return pluses - minuses;
}

void print(Pt T)
{
    if (T == NULL)
        return;
    print(T->l);
    print(T->r);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    root_plus = root_minus = NULL;
    int d = 0, n;
    scanf("%d", &n);
    forn(j, n)
    {
        int t;
        scanf("%d", &t);
        if (t == 1)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            a += d;
            b += d;
            add_seg(a, b);
        }
        else
        {
            int p;
            scanf("%d", &p);
            d = get(p);
            printf("%d\n", d);
        }
    }
}

