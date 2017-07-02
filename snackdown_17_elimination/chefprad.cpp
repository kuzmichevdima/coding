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

const int maxn = 255;

int a1[maxn];
int b[maxn];
int allow;
int n, m;

int f(i64 shift) {
    if (shift < -2e9)
        shift = 2e9;
    if (shift > 2e9)
        shift = 2e9;
    int pointer = 0;
    int result = 0;
    forn(i, n) {
        if (pointer == m)
            break;
        i64 value = shift + a1[i];
        // cout << value << " " << pointer << " " << result << endl;
        while(pointer < m && (b[pointer] < value - allow))
            pointer++;
        if (pointer < m && abs((i64)b[pointer] - value) <= allow) {
            result++;
            pointer++;
        }
    }
    return result;
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
        scanf("%d%d%d", &n, &m, &allow);
        forn(i, n)
            scanf("%d", &a1[i]);
        forn(i, m)
            scanf("%d", &b[i]);
        sort(a1, a1 + n);
        sort(b, b + m);
        //f(-1);
        //exit(0);
        // fore(j, -10, 10)
        //    printf("j = %d f = %d\n", j, f(j));
        /*while((i64)finish - start >= 3) {
            printf("%d %d\n", start, finish);
            int m1 = start + ((i64)finish - start) / 3;
            int m2 = finish - ((i64)finish - start) / 3;
            if (f(m1) > f(m2))
                finish = m2;
            else start = m1;
        }
        int ans = 0;
        fore(j, start, finish)
            ans = max(ans, f(j));*/
        int ans = 0;
        forn(i, n)
            forn(j, m) {
                ans = max(ans, f((i64)b[j] + allow - a1[i]));
                ans = max(ans, f((i64)b[j] - allow - a1[i]));
            }
        printf("%d\n", ans);
    }
}

