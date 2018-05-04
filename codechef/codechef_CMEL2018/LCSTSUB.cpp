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

struct Node {
    i64 x;
    int y, maxx, value;
    Node* L, *R;
    Node(i64 x, int value) : x(x), y(rand()), maxx(value), value(value), L(NULL), R(NULL) {}
};

typedef Node* Pt;

int get_max(Pt& P) {
    return P == NULL ? 0 : P->maxx;
}

void recalc(Pt& P) {
    if (P == NULL)
        return;
    P->maxx = max(P->value, max(get_max(P->L), get_max(P->R)));
}

void split(Pt P, i64 x, Pt& L, Pt& R) {
    if (P == NULL) {
        L = R = NULL;
        return;
    }
    if (P->x <= x) {
        L = P;
        split(P->R, x, L->R, R);
    } else {
        R = P;
        split(P->L, x, L, R->L);
    }
    recalc(L);
    recalc(R);
}

void merge(Pt& P, Pt L, Pt R) {
    if (L == NULL) {
        P = R;
        return;
    }
    if (R == NULL) {
        P = L;
        return;
    }
    if (L->y > R->y) {
        P = L;
        merge(P->R, P->R, R);
    } else {
        P = R;
        merge(P->L, L, P->L);
    }
    recalc(L);
    recalc(R);
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
    int ans = 0;
    Pt root = NULL;
    forn(i, n) {
        int a_tmp, l_tmp;
        scanf("%d%d", &a_tmp, &l_tmp);
        i64 a_i = a_tmp ^ ans;
        i64 l_i = l_tmp ^ ans;
        Pt A, B, C, D, E, F, target;
        split(root, a_i + l_i, A, B);
        split(A, a_i - l_i - 1, C, target);
        int cur_dp = get_max(target) + 1;
        ans = max(ans, cur_dp);
        printf("%d\n", ans);
        split(target, a_i, D, E);
        Node* nnew = new Node(a_i, cur_dp);
        merge(F, D, nnew);
        merge(target, F, E);
        merge(A, C, target);
        merge(root, A, B);
    }
}

