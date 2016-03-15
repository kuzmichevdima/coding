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

const int maxn = 1e5+5;

int a[maxn];
int n;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d\n", &n);
    forn(j, n)
    {
        char c;
        scanf("%c", &c);
        a[j] = c - '0';
    }
    int curL= 0;
    while(curL + 1 < n && a[curL + 1] != a[curL])
        curL++;
    if (curL == n - 1)
    {
        printf("%d\n", n);
        exit(0);
    }
    int curR = n - 1;
    while(curR - 1 >= 0 && a[curR - 1] != a[curR])
        curR--;
    //printf("curL = %d curR = %d\n", curL, curR);
    if (curL + 1 == curR)
    {
        fore(j, curR, n - 1)
            a[j] = 1 - a[j];
    }
    else
    {
        fore(j, curL + 1, curR - 1)
            a[j] = 1 - a[j];
    }
//    forn(j, n)
  //      printf("%d", a[j]);
    int answer = 1;
    int last = 0;
    int cur = 1;

    while(true)
    {
        while(cur < n && a[cur] != 1 - a[last])
            cur++;
        if (cur < n)
        {
            last = cur;
            answer++;
        }
        else break;
    }
    printf("%d", answer);
}
