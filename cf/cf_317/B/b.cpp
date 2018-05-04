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
    int n, k;
    scanf("%d%d", &n, &k);
    vi a(n), ans;
    forn(j, n)
        a[j] = rand() % 15;
        //scanf("%d", &a[j]);
    sort(a.begin(), a.end());
    int best = 1e9;
    do
    {
        int nnew = 0;
        forn(j, n - k) 
            nnew += abs(a[j + k] - a[j]);
        if (nnew < best)
        {
            best = nnew;
            ans = a;
        }
    }
    while(next_permutation(a.begin(), a.end()));
    printf("best = %d\n", n);
    vi b(n);
    for (int x : ans)
        printf("%d ", x);
    //reverse(a.begin(), a.end());
    printf("\n");
    for (int x : a)
        printf("%d ", x);
    printf("\n========\n");
    int pos = 0;
    forn(start, k)
    {
        int cur = start;
        while(cur < n)
        {
            b[cur] = a[pos];
            pos++;
            cur += k;
           // printf("cur = %d\n", cur);
        }
    }
    int my_ans = 0;
    forn(j, n - k)
        my_ans += abs(b[j + k] - b[j]);
    printf("\n");
    for (int x : b)
        printf("%d ", x);
    printf("my_ans = %d\n", my_ans);
}
