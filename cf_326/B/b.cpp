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

const int MOD = 1e9+7;
const int maxn = 1e6+5;

vi tree[maxn];
int a[maxn];
int prec[maxn];
int a_sorted[maxn];

inline void add(int & x, int y)
{
    x = (x + y) % MOD;
}

void upd(int number, int i, int L, int R, int A, int B, int val)
{
    if (A >= R || L >= B)
        return;
    if (A == L && B == R)
    {
        add(tree[number][i], val);
        return;
    }
    int M = (L + R) / 2;
    upd(number, i * 2, L, M, A, min(M, B), val);
    upd(number, i * 2 + 1, M, R, max(A, M), B, val);
}

int get(int number, int i, int L, int R, int pos)
{
    if (L + 1 == R)
        return tree[number][i];
    int M = (L + R) / 2;
    if (pos < M)
        return (get(number, i * 2, L, M, pos) + tree[number][i]) % MOD;
    else 
        return (get(number, i * 2 + 1, M, R, pos) + tree[number][i]) % MOD;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    i64 L;
    cin >> n >> L >> k;
    n = min((i64)n, L);
    forn(j, n)
    {
        scanf("%d", &a[j]);
        a_sorted[j] = a[j];
    }
    sort(a_sorted, a_sorted + n);
    forn(j, n)
        prec[j] = lower_bound(a_sorted, a_sorted + n, a[j]) - a_sorted;
    i64 blocks = (L % n == 0 ? L / n : L / n + 1);
    int in_last_block = (L % n == 0 ? n : L % n);
    k = min((i64)k, blocks);
    //cout << blocks << " " << in_last_block << " " << k << endl;
    forn(len, k + 1)
        tree[len].resize(4 * n);
    upd(0, 1, 0, n, 0, n, 1);
    int answer = 0;
    forn(len, k)
        forn(pos, n)
        {
            int cur = get(len, 1, 0, n, prec[pos]);      
            if (cur == 0)
                continue;
//            printf("len = %d pos = %d cur = %d\n", len, pos, cur);
            int places = (pos + 1 <= in_last_block ? blocks - len: blocks - len - 1) % MOD;
            int to_add = (i64)places * cur % MOD;
  //          printf("to_add = %d\n", to_add);
            add(answer, to_add);
            upd(len + 1, 1, 0, n, prec[pos], n, cur);
        }
    printf("%d", answer);
}
