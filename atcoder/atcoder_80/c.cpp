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

const int maxn = 2e5+5;
const int inf = 1e9;
int a[maxn];
pii tree[2][maxn * 4];

void build(int number, int i, int l, int r) {
    if (l + 1 == r) {
        tree[number][i] = l % 2 == number ? mp(a[l], l) : mp(inf, -1);
        return;
    }
    int m = (l + r) / 2;
    build(number, i * 2, l, m);
    build(number, i * 2 + 1, m, r);
    tree[number][i] = min(tree[number][i * 2], tree[number][i * 2 + 1]);
}

pii get(int number, int i, int l, int r, int a, int b) {
    if (a >= r || l >= b)
        return mp(inf, -1);
    if (l >= a && r <= b)
        return tree[number][i];
    int m = (l + r) / 2;
    return min(get(number, i * 2, l, m, a, b), get(number, i * 2 + 1, m, r, a, b));
}

int n;
int cnt = 0;

struct Elem {
    int code, index;
    pii value;
};

bool operator < (Elem first, Elem second) {
    if (first.code < 0) {
        if (second.code < 0)
            return first.code < second.code;
        else return true;
    } else if (second.code < 0)
        return false;
    if (first.code == second.code)
        return first.index < second.index;
    return first.value < second.value;
}

set <Elem> S[maxn];
int cur_code;

int go(int l, int r) {
    if (l > r)
        return 0;
    if (l + 1 == r) {
        cnt++;
        S[cnt].insert({0, 0, mp(a[l], a[l + 1])});
        return cnt;
    }
    //printf("go %d %d\n", l, r);
    pii first = get(l % 2, 1, 0, n, l, r + 1);
    pii second = get(1 - l % 2, 1, 0, n, first.se + 1, r + 1);
    //printf("found %d %d\n", first.fi, second.fi);
    vi set_num(3);
    set_num[0] = go(l, first.se - 1);
    set_num[1] = go(first.se + 1, second.se - 1);
    set_num[2] = go(second.se + 1, r);
    //forn(j, 3)
      //  printf("set size is %d\n", (int)S[set_num[j]].size());
    int biggest = 0;
    fore(j, 1, 2)
        if (S[set_num[j]].size() > S[set_num[biggest]].size())
            biggest = j;
    cur_code++;
    S[set_num[biggest]].insert({-cur_code, 0, mp(first.fi, second.fi)});
    forn(small, 3) {
        if (small == biggest)
            continue;
        cur_code++;
        int cur_index = 0;
        for (const auto& x : S[set_num[small]]) {
            S[set_num[biggest]].insert({cur_code, cur_index, x.value});
            cur_index++;
        }
        S[set_num[small]].clear();
    }
    //printf("for l = %d r = %d set size %d\n", l, r, (int)S[set_num[biggest]].size());
    return set_num[biggest];
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
    forn(j, n)
        scanf("%d", &a[j]);
        //a[j] = j + 1;
        //a[j] = j + 1;
    //random_shuffle(a, a + n);
    //forn(j, n) {
    //    scanf("%d", &a[j]);
    forn(number, 2)
        build(number, 1, 0, n);
    int ans_num = go(0, n - 1);
    for (auto x : S[ans_num])
        printf("%d %d ", x.value.fi, x.value.se);
}

