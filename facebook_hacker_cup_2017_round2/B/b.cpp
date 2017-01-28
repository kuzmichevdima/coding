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

#define ld long double

const int maxn = 8e5+5;
const double eps = 1.0e-6;

int X[maxn];
int H[maxn];
bool tree[maxn * 4];
int place[maxn];
int n;
pii order[maxn];
ld area[maxn];

bool check(int i, int L, int R, int A, int B) {
    if (L == A && R == B)
        return tree[i];
    if (L >= B || A >= R)
        return false;
    int M = (L + R) / 2;
    return check(i * 2, L, M, A, min(B, M)) || check(i * 2 + 1, M, R, max(A, M), B);
}

int find_right(int pl) {
    int lower = pl + 1;
    int upper = n - 1;
    while(lower < upper) {
        int middle = (lower + upper) / 2;
        if (check(1, 0, n, pl + 1, middle + 1))
            upper = middle;
        else lower = middle + 1;
    }
    return check(1, 0, n, pl + 1, lower + 1) ? order[lower].se : -1;
}

int find_left(int pl) {
    int lower = 0;
    int upper = pl - 1;
    while(lower < upper) {
        int middle = (lower + upper) / 2 + 1;
        if (check(1, 0, n, middle, pl))
            lower = middle;
        else upper = middle - 1;
    }
    return check(1, 0, n, lower, pl) ? order[lower].se : -1;
}

void upd(int i, int L, int R, int pos, bool val) {
    if (L + 1 == R) {
        tree[i] = val;
        return;
    }
    int M = (L + R) / 2;
    if (pos < M)
        upd(i * 2, L, M, pos, val);
    else upd(i * 2 + 1, M, R, pos, val);
    tree[i] = tree[i * 2] || tree[i * 2 + 1];
}

inline bool eclipse(int num1, int num2) {
    return H[num1] - H[num2] >= abs(X[num1] - X[num2]);
}

inline void del(int num, ld & cur) {
    //printf("del %d\n", num);
    cur -= area[num];
    upd(1, 0, n, place[num], false);
}

inline void add(int num) {
    //printf("add place = %d\n", place[num]);
    upd(1, 0, n, place[num], true);
}

inline ld calc(int num1, int num2) {
    ld deltax = X[num2] - X[num1];
    ld d = (deltax - (H[num2] - H[num1])) / 2;    
    //printf("calc d = %.5lf\n", d);
    return d * (2 * H[num1] - d) / 2 + (deltax - d) * (H[num2] + H[num1] - d) / 2;
}

inline void set_and_apply(ld & x, ld val, ld & cur) {
    cur -= x;
    x = val;
    cur += x;
}

int main() {
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        fprintf(stderr, "test %d\n", test);
        int Ax, Bx, Cx, Ah, Bh, Ch;
        scanf("%d", &n);
        scanf("%d%d%d%d", &X[0], &Ax, &Bx, &Cx);
        fore(j, 1, n - 1)
            X[j] = ((i64)X[j - 1] * Ax + Bx) % Cx + 1;
        scanf("%d%d%d%d", &H[0], &Ah, &Bh, &Ch);
        fore(j, 1, n - 1)
            H[j] = ((i64)H[j - 1] * Ah + Bh) % Ch + 1;
        forn(j, n)
            order[j] = mp(X[j], j);
        sort(order, order + n);
        forn(j, n)
            place[order[j].se] = j;
        memset(tree, 0, sizeof(tree));
        ld cur = 0.0;
        ld ans = 0;
        ld leftest = 0;
        forn(j, n) {
            printf("\n==============\nj = %d X = %d  H = %d\n", j, X[j], H[j]);
            int R = find_right(place[j]);
            if (R != -1 && eclipse(R, j)) {

                ans += cur;
                continue;
            }
            int L = find_left(place[j]);
            //printf("L = %d R = %d\n", L, R);
            if (L != -1 && eclipse(L, j)) {

                ans += cur;
                continue;
            }
            //printf("%d not eclipsed\n", j);
            while(R != -1 && eclipse(j, R)) {
                del(R, cur);    
                R = find_right(place[j]);
            }
            //printf("R = %d\n", R);
            if (R == -1)
                area[j] = (i64)H[j] * H[j] * 1.0 / 2;
            else area[j] = calc(j, R);
            printf("area[%d] = %.5Lf\n", j, area[j]);
            cur += area[j];
            cout << cur << endl;
            assert(cur > 0);
            while(L != -1 && eclipse(j, L)) {
                del(L, cur);
                L = find_left(place[j]);
            }
            if (L != -1) {
                set_and_apply(area[L], calc(L, j), cur);
            } else {
                set_and_apply(leftest, (i64)H[j] * H[j] * 1.0 / 2, cur);
            }
            printf("j = %d\n", j);
            assert(cur > 0);
            ans += cur;

            //printf("cur = %.5lf\n", (double)cur);
            add(j);
        }
        printf("Case #%d: %.10lf\n", test + 1, (double)ans);
        cout << ans << endl;
        fprintf(stderr, "Case #%d: %.10lf\n", test + 1, (double)ans);
    }
}
