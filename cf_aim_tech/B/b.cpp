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

const int maxn = 1e6+5;
const int max_prime = 1e5;
const i64 inf = 1e18;

int a[maxn];
bool mark[max_prime + 5];
int cnt[maxn];
int penalty[maxn];
int n;
i64 A, B, answer;

inline i64 solve(int div, int L, int R)
{
    int bad_start = n, bad_finish = -1;
    fore(pos, L, R)
    {
        int rem = a[pos] % div;
        if (rem == 0)
            penalty[pos] = 0;
        else if (rem == 1 || rem == div - 1)
            penalty[pos] = 1;
        else
        {
            penalty[pos] = 0;
            if (bad_start == n)
                bad_start = pos;
            bad_finish = pos;
        }
    }
    fore(pos, L, R)
        cnt[pos] = (pos == L ? penalty[L] : cnt[pos - 1] + penalty[pos]);
    i64 result = (bad_start == n ? B * cnt[R] : inf);
    i64 optimal = inf;
    for (int start = R; start >= L; start--)
    {
        if (start >= bad_finish)
            optimal = min(optimal, A * start - B * cnt[start]);
        if (start <= bad_start)
        {
            i64 local = A * (-start + 1) + B * ((start == L ? 0 : cnt[start - 1]) + cnt[R]) + optimal;
            result = min(result, local);
        }
    }
    return result;
}

inline void work_with(int x, int L, int R)
{
    for (int d = 2; d * d <= x; d++) if (x % d == 0 && !mark[d])
    {
        while(x % d == 0)
            x /= d;
        answer = min(answer, solve(d, L, R));
    }
    if (x != 1)
        answer = min(answer, solve(x, L, R));
}

void precalc()
{
    for (int i = 2; i <= max_prime; i++) if (!mark[i])
        for (int j = 2 * i; j <= max_prime; j += i)
            mark[j] = true;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    cin >> n >> A >> B;
    forn(i, n)
        scanf("%d", &a[i]);
    precalc();
    answer = inf;
    work_with(a[0], 1, n - 1);
    work_with(a[n - 1], 0, n - 2);
    cout << answer;
}
