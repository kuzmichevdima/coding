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

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    vi ans;
    int n;
    scanf("%d", &n);
    fore(prime, 2, n)
    {
        bool flag = true;
        for (int d = 2; d * d <= prime; d++)
            if (prime % d == 0)
            {
                flag = false;
                break;
            }
        if (!flag)
            continue;
        int cnt = 1;
        int cur = prime;
        ans.pb(prime);
        while(cur * prime <= n)
        {
            cur *= prime;
            cnt++;
            ans.pb(cur);

        }
/*        int start = 1;
        int finish = cnt;
        while(start <= finish)
        {
            int middle = (start + finish) / 2;
            int power = 1;
            forn(j, middle)
                power *= prime;
            ans.pb(power);
            if (middle - 1 - start > finish - (middle + 1))
            {
                finish = middle - 1;
            }
            else start = middle + 1;
        }*/
    }
    printf("%d\n", (int)ans.size());
    for (int x : ans)
        printf("%d ", x);
}
