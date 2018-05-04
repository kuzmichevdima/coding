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
#include <stack>

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

int a[maxn];
int tree[maxn * 4];

int get_min(int i, int L, int R, int A, int B) {
    if (A >= R || L >= B)
        return -1;
    if (L >= A && R <= B)
        return tree[i];
    int M = (L + R) / 2;
    int g1 = get_min(i * 2, L, M, A, B);
    int g2 = get_min(i * 2 + 1, M, R, A, B);
    if (g1 == -1)
        return g2;
    if (g2 == -1)
        return g1;
    return a[g1] < a[g2] ? g1 : g2;
}

void build(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i] = L;
        return;
    }
    int M = (L + R) / 2;
    build(i * 2, L, M);
    build(i * 2 + 1, M, R);
    tree[i] = a[tree[i * 2]] < a[tree[i * 2 + 1]] ? tree[i * 2] : tree[i * 2 + 1];
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n;
        scanf("%d", &n);
        forn(i, n)
            scanf("%d", &a[i]);
        vi b(n);
        forn(i, n)
            scanf("%d", &b[i]);
        stack<int> bb;
        vi nextb(n);
        for (int i = n - 1; i >= 0; --i) {
            while(!bb.empty() && b[bb.top()] <= b[i])
                bb.pop();
            nextb[i] = bb.empty() ? n : bb.top();
            bb.push(i);
        }
        int ans = 0;
        build(1, 0, n);
        stack<pii> changes;
        forn(i, n) {
            while(!changes.empty() && changes.top().fi < i)
                changes.pop();
            //printf("\n============\ni = %d\n", i);
            int reala = changes.empty() ? a[i] : changes.top().se;
            if (reala < b[i]) {
                ans = -1;
                break;
            }
            if (reala == b[i])
                continue;
            ans++;
            int border = nextb[i];
            int s = i + 1;
            int f = n;
            while(s < f) {
                int m = (s + f) / 2;
                int minn = get_min(1, 0, n, i + 1, m + 1);
                if (a[minn] < b[i]) {
                    f = m;
                } else s = m + 1;
            }
           // printf("s = %d\n", s);
            border = min(border, s);
            /*printf("i = %d nextb[i] = %d\n", i, nextb[i]);
            forn(i, n)
                printf("%d ", a[i]);
            printf("\n");
            printf("i = %d border = %d\n", i, border);*/
            //fore(j, i, border - 1)
            //    a[j] = b[i];
            changes.push({border - 1, b[i]});
        }
        printf("%d\n", ans);
    }
}

