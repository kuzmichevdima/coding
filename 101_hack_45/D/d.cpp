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

const i64 mod = 1e9+7;

i64 bin_pow(i64 x, int p) {
    if (p == 0)
        return 1;
    i64 y = bin_pow(x, p / 2);
    i64 res = y * y % mod;
    if (p & 1)
        res = res * x % mod;
    return res;
}

i64 norm(i64 x) {
    if (x < 0)
        x = mod - (-x % mod);
    return x % mod;
}

const int maxn = 1e5 + 5;

i64 tree[maxn * 4];
i64 pows[maxn];
int coeff[maxn];

void upd(int i, int L, int R, int pos, int val) {
    if (L + 1 == R) {
        tree[i] = norm(pows[pos] * val);
        return;
    }
    int m = (L + R) / 2;
    if (pos < m)
        upd(i * 2, L, m, pos, val);
    else upd(i * 2 + 1, m, R, pos, val);
    tree[i] = norm(tree[i * 2] + tree[i * 2 + 1]);
}

i64 get(int i, int L, int R, int A, int B) {
    if (L == A && R == B)
        return tree[i];
    if (A >= R || L >= B)
        return 0;
    int m = (L + R) / 2;
    return norm(get(i * 2, L, m, A, min(m, B)) + get(i * 2 + 1, m, R, max(A, m), B));
}

int main() {
    int n, a, b, q;
    scanf("%d%d%d%d", &n, &a, &b, &q);
    i64 P = norm(-(i64)b * bin_pow(a, mod - 2));
    pows[0] = 1;
    fore(j, 1, n) {
        pows[j] = norm(pows[j - 1] * P);
    }
    forn(j, n) {
        scanf("%d", &coeff[j]);
        upd(1, 0, n, j, coeff[j]);
    }
    forn(it, q) {
        int typ;
        scanf("%d", &typ);
        if (typ == 1) {
            int pos, val;
            scanf("%d%d", &pos, &val);
            coeff[pos] = val;
            upd(1, 0, n, pos, val);
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            if (b == 0) {
                if (coeff[l] == 0)
                    printf("Yes\n");
                else printf("No\n");
            } else {
                i64 s1 = get(1, 0, n, 0, r + 1);
                i64 s2 = get( 1, 0, n, 0, l);
                i64 s = norm(s2 - s1);
                if (s == 0)
                    printf("Yes\n");
                else printf("No\n");
            }
        }
    }
}
