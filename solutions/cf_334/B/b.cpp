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
const i64 MOD = 1e9+7;

bool mark[maxn];
int edge[maxn];

void dfs(int v)
{
    mark[v] = true;
    if (!mark[edge[v]])
        dfs(edge[v]);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int p, k;
    scanf("%d%d", &p, &k);
    if (k <= 1)
    {
        i64 answer = 1;
        forn(j, p - (1 - k))
            answer = (answer * p) % MOD;
        cout << answer;
        exit(0);
    }
    fore(j, 1, p - 1)
    {
        edge[(i64)j * k % p] = j;
    }
    i64 answer = 1;
    fore(j, 1, p - 1) if (!mark[j])
    {
        dfs(j);
        answer = (answer * p) % MOD;
    }
    cout << answer;
}
