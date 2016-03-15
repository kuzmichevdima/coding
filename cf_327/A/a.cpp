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

const int n = 8;

vi a;

vi get(vi v)
{
    int start = 0;
    fore(j, 1, v.size() - 1)
    {
        if (v[j] == v[j - 1])
            continue;
        
    }
}

void go(int step)
{
    if (step == n)
    {
        vi b = a;
        int cnt = 0;
        while(true)
        {
            vi c(n);
            c[0] = b[0];
            c[n - 1] = b[n - 1];
            fore(j, 1, n - 2)
            {
                int tmp = b[j - 1] + b[j] + b[j + 1];
                if (tmp >= 2)
                    c[j] = 1;
                else c[j] = 0;
            }
            if (c == b)
                break;
            cnt++;
            b = c;
        }
        forn(j, n)
            printf("%d ", a[j]);
        printf(" ---> ");
        forn(j, n)
            printf("%d ", b[j]);
        printf("cnt = %d\n", cnt);
        return;
    }
    a[step] = 0;
    go(step + 1);
    a[step] = 1;
    go(step + 1);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    a.resize(n);
    go(0);
}
