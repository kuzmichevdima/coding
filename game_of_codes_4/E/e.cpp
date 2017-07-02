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
    int x, y, sz;
    Treap * L, * R;
    Treap(int x) : x(x), y(rand()), sz(1), L(NULL), R(NULL) {}
};
typedef Treap * Pt;

inline int get_size(const Pt T) {
    return T == NULL ? 0 : T->sz;
}

void recalc(const Pt & T) {
    if (T == NULL)
        return;
    T->sz = get_size(T->L) + get_size(T->R) + 1;
}

void split(Pt T, int sz, Pt & A, Pt & B) {
    if (T == NULL) {
        A = B = NULL;
        return;
    }
    int left_sz = get_size(T->L);
    if (sz < left_sz + 1) {
        B = T;
        split(T->L, sz, A, B->L);
        recalc(B);
    } else {
        A = T;
        split(T->R, sz - left_sz - 1, A->R, B);
        recalc(A);
    }
}

void merge(Pt & T, Pt A, Pt B) {
    if (A == NULL) {
        T = B;
        return;
    }
    if (B == NULL) {
        T = A;
        return;
    }
    if (A->y > B->y) {
        T = A;
        merge(T->R, T->R, B);
    } else {
        T = B;
        merge(T->L, A, T->L);
    }
    recalc(T);
}

void print(Pt T) {
    if (T == NULL)
        return;
    print(T->L);
    printf("%d ", T->x);
    print(T->R);
}

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
    Pt root = NULL;
    forn(j, n) {
        int x;
        scanf("%d", &x);
        auto nnew = new Treap(x);
        merge(root, root, nnew);
    }
    int queries;
    scanf("%d", &queries);
    forn(j, queries) {
        int l1, r1, l2, r2;
        Pt p1, p2, p3, p5, p6, p7, left_part, right_part;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
      //  printf("l1 = %d r1 = %d l2 = %d r2 = %d\n", l1, r1, l2, r2);
        split(root, r2, p1, p2);
//        printf("p1 size %d p2 size %d\n", get_size(p1), get_size(p2));
        split(p1, l2 - 1, p3, right_part);
  //      printf("p3 size %d right_part size %d\n", get_size(p3), get_size(right_part));
        split(p3, r1, p5, p6);
    //    printf("p5 size %d p6 size %d\n", get_size(p5), get_size(p6));
        split(p5, l1 - 1, p7, left_part);
        merge(root, p7, right_part);
      //  printf("root size %d\n", root->sz);
        merge(root, root, p6);
        //printf("root size %d\n", root->sz);
        merge(root, root, left_part);
        //printf("root size %d\n", root->sz);
        merge(root, root, p2);
    }
    print(root);
}
