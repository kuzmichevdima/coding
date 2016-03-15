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

const int maxn = 1e5 + 5;

i64 tree[maxn * 4];
int x[maxn];
int y[maxn];
int n;
set <int> order;

inline i64 calc(int i, int j)
{
    return (i64)x[i] * y[j] - (i64)x[j] * y[i];
}

i64 get(int i, int L, int R, int A, int B)
{
    if (L == A && R == B)
        return tree[i];
    if (L >= B || A >= R)
        return 0;
    int M = (L + R) / 2;
    return get(i * 2, L, M, A, min(M, B)) + get(i * 2 + 1, M, R, max(M, A), B);
}

inline i64 get(int L, int R)
{
    if (L > R)
        return 0;
    return get(1, 1, n + 1, L, R + 1);
}

void upd(int i, int L, int R, int pos, i64 val)
{
    if (L + 1 == R)
    {
        tree[i] = val;
        return;
    }
    int M = (L + R) / 2;
    if (pos < M)
        upd(i * 2, L, M, pos, val);
    else upd(i * 2 + 1, M, R, pos, val);
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

inline void upd(int pos, i64 val)
{
    upd(1, 1, n + 1, pos, val);
}

void build(int i, int L, int R)
{
    if (L + 1 == R)
    {
        tree[i] = calc(L, (L == n ? 1 : L + 1));
        return;
    }
    int M = (L + R) / 2;
    build(i * 2, L, M);
    build(i * 2 + 1, M, R);
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
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
    fore(j, 1, n)
    {
        scanf("%d%d", &x[j], &y[j]);
        order.insert(j);
    }
    build(1, 1, n + 1);
    int m;
    scanf("%d\n", &m);
    forn(q, m)
    {
        //printf("iteration %d\n", q);
        char typ;
        scanf("%c", &typ);
        if (typ == '+' || typ == '-')
        {
            int number;
            scanf("%d\n", &number);
            if (typ == '-')
                order.erase(number);
            set <int> :: iterator it = order.upper_bound(number);
            int next_number = (it == order.end() ? *order.begin() : *it);
            int prev_number;
            if (it == order.begin())
                prev_number = *order.rbegin();
            else
            {
                it--;
                prev_number = *it;
            }
            //printf("number = %d prev_number = %d next_number = %d\n", number, prev_number, next_number);
            if (typ == '+')
            {
                upd(prev_number, calc(prev_number, number));
                upd(number, calc(number, next_number));
                order.insert(number);
            }
            else
            {
                upd(prev_number, calc(prev_number, next_number));
                upd(number, 0);
                //order.erase(number);
            }
        }
        else if (typ == '?')
        {
            int L, R;
            scanf("%d%d\n", &L, &R);
            //printf("ask %d %d\n", L, R);
            i64 ans;
            if (L <= R)
                ans = get(L, R - 1);
            else ans = get(L, n) + get(1, R - 1);
            ans += calc(R, L);
            cout << ans << endl;
        }
    }
}

