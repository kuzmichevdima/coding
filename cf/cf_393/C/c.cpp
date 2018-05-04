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

int delta[maxn * 4];
int minn[maxn * 4];
int maxx[maxn * 4];
int typ[maxn];
int param1[maxn];
int param2[maxn];

inline void push(int i, bool is_leaf) {
    minn[i] += delta[i];
    maxx[i] += delta[i];
    if (!is_leaf) {
        delta[i * 2] += delta[i];
        delta[i * 2 + 1] += delta[i];
    }
    delta[i] = 0;
}

void add(int i, int L, int R, int A, int B, int val) {
    push(i, L + 1 == R);
    if (L == A && R == B) {
        delta[i] += val;
        push(i, L + 1 == R);
        return;
    }
    if (A >= R || L >= B)
        return;
    int M = (L + R) / 2;
    add(i * 2, L, M, A, min(B, M), val);
    add(i * 2 + 1, M, R, max(A, M), B, val);
    minn[i] = min(minn[i * 2], minn[i * 2 + 1]);
    maxx[i] = max(maxx[i * 2], maxx[i * 2 + 1]);
}

int get(int i, int L, int R) {
    push(i, L + 1 == R);
    if (maxx[i] >= 1 && minn[i] <= 1) {
        if (L + 1 == R)
            return L;
        int M = (L + R) / 2;
        int g1 = get(i * 2 + 1, M, R);
        if (g1 != -1)
            return g1;
        return get(i * 2, L, M);
    } else return -1;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    vector <pii> list;
    forn(i, n) {
        scanf("%d%d", &param1[i], &typ[i]);
        if (typ[i] == 1) {
            scanf("%d", &param2[i]);
            list.pb(mp(param1[i], param2[i]));
        }
    }
    sort(list.begin(), list.end());
    vi values(list.size());
    forn(i, list.size())
        values[i] = list[i].fi;
    forn(i, n) {
        int pos = upper_bound(values.begin(), values.end(), param1[i]) - values.begin();
        if (typ[i] == 0) {
            add(1, 0, list.size(), 0, pos, -1);
        } else add(1, 0, list.size(), 0, pos, +1);
        int ans = get(1, 0, (int)list.size());
        printf("%d\n", ans == -1 ? -1 : list[ans].se);
    }

}
