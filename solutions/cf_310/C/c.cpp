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

struct Query
{
    int x, y;
    char typ;
};

const int maxn = 2e5+5;

Query q[maxn];

void upd(vi & tree, int i, int L, int R, int A, int B, int val)
{
    if (A >= R || L >= B)
        return;
    if (A == L && B == R)
    {
        tree[i] = max(tree[i], val);
        return;
    }
    int M = (L + R) / 2;
    upd(tree, i * 2, L, M, A, min(M, B), val);
    upd(tree, i * 2 + 1, M, R, max(A, M), B, val);
}

int get(vi & tree, int i, int L, int R, int pos)
{
    if (L + 1 == R)
        return tree[i];
    int M = (L + R) / 2;
    if (pos < M)
        return max(tree[i], get(tree, i * 2, L, M, pos));
    else return max(tree[i], get(tree, i * 2 + 1, M, R, pos));
}

void process(vi & v)
{
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, Q;
    scanf("%d%d", &n, &Q);
    vi uniq_x, uniq_y, tree_col, tree_row;
    forn(j, Q)
    {
        scanf("%d%d %c", &q[j].x, &q[j].y, &q[j].typ);
        uniq_x.pb(q[j].x);
        uniq_y.pb(q[j].y);
    }
    uniq_x.pb(0);
    uniq_y.pb(0);
    process(uniq_x);
    process(uniq_y);
    int X = uniq_x.size();
    int Y = uniq_y.size();
/*    for (int x : uniq_x)
        printf("%d ", x);
    printf("\n");
    for (int y : uniq_y)
        printf("%d ", y);
    exit(0);*/
    tree_col.resize(X * 4, 0);
    tree_row.resize(Y * 4, 0);
//    build(tree_col, 1, 0, X);
  //  build(tree_row, 1, 0, Y);
    forn(j, Q)
    {
        q[j].x = lower_bound(uniq_x.begin(), uniq_x.end(), q[j].x) - uniq_x.begin();
        q[j].y = lower_bound(uniq_y.begin(), uniq_y.end(), q[j].y) - uniq_y.begin();
        int limit_number;
//        printf("real x = %d y = %d\n", q[j].x, q[j].y);
        if (q[j].typ == 'U')
        {
            limit_number = get(tree_col, 1, 0, X, q[j].x);
  //          printf("limit_number = %d\n", limit_number);
            printf("%d\n", uniq_y[q[j].y] - uniq_y[limit_number]);
//            exit(0);
//            printf("upd tree_row [%d; %d) by %d\n", limit_number + 1, q[j].y + 1, q[j].x);
            upd(tree_row, 1, 0, Y, limit_number + 1, q[j].y + 1, q[j].x);
            upd(tree_col, 1, 0, X, q[j].x, q[j].x + 1, q[j].y);
        }
        else
        {
            limit_number = get(tree_row, 1, 0, Y, q[j].y);
    //        printf("limit_number = %d\n", limit_number);
            printf("%d\n", uniq_x[q[j].x] - uniq_x[limit_number]);
            upd(tree_col, 1, 0, X, limit_number + 1, q[j].x + 1, q[j].y);
      //      printf("upd tree_row [%d; %d) by %d\n", q[j].y, q[j].y + 1, q[j].x);
            upd(tree_row, 1, 0, Y, q[j].y, q[j].y + 1, q[j].x);
        }
    }
}
