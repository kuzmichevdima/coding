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
    Elem * move0, * move1;
    int cnt, x;
    Elem() : move0(NULL), move1(NULL), cnt(0), x(0) {}
};

typedef Elem * Pt;

Pt root;

int get(Pt p) {
    return p == NULL ? 0 : p->cnt;
}

void recalc(Pt & p) {
    assert(p->x == 0);
    p->cnt = get(p->move0) + get(p->move1);
}

const int maxbit = 30;

void add(int x) {
    Pt cur = root;
    vector <Pt> way;
    for (int num = maxbit; num >= 0; num--) {
        way.pb(cur);
        int bit = (x & (1 << num)) >> num;
//        printf("num = %d bit = %d\n", num, bit);
        if (bit == 0) {
            if (cur->move0 == NULL) {
  //              printf("create new\n");
                cur->move0 = new Elem();
            }
            cur = cur->move0;
        } else {
            if (cur->move1 == NULL)
                cur->move1 = new Elem();
            cur = cur->move1;
        }
    }
    cur->x++;
    cur->cnt = cur->x;
    for (int j = way.size() - 1; j >= 0; j--)
        recalc(way[j]);
}

const int maxn = 1e6+5;

int a[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    a[0] = 0;
    forn(j, n) {
        int x;
        scanf("%d", &x);
        a[j + 1] = a[j] ^ x;
    }
    root = new Elem();
    add(0);
    i64 ans = 0;
    fore(j, 1, n) {
//        printf("a[%d] = %d\n", j, a[j]);
        Pt cur = root;
        for (int bit = maxbit; bit >= 0; bit--) {
            int bit1 = ((1 << bit) & a[j]) >> bit;
            int bit2 = ((1 << bit) & k) >> bit;
            if (bit1 == 1 && bit2 == 1) {
                if (cur->move0 == NULL)
                    break;
                cur = cur->move0;
            } else if (bit1 == 0 && bit2 == 0) {
                int delta = get(cur->move1);
                ans += delta;
                if (cur->move0 == NULL)
                    break;
                cur = cur->move0;
            } else if (bit1 == 1 && bit2 == 0) {
               // printf("j = %d bit1 = %d bit2 = %d\n", j, bit1, bit2);
                int delta = get(cur->move0);
             //   printf("detla = %d in case (1, 0)\n", delta);
                ans += delta;
                if (cur->move1 == NULL)
                    break;
                cur = cur->move1;
            } else {
  //              printf("j = %d bit1 = %d bit2 = %d\n", j, bit1, bit2);
                if (cur->move1 == NULL)
                    break;
    //            else printf("can move\n");
                cur = cur->move1;
            }
            if (bit == 0) {
                int delta = get(cur);
     //           printf("delta = %d\n", delta);
                ans += delta;
            }
        }
        add(a[j]);
    }
    cout << ans;
}
