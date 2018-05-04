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

inline int get(int start, int finish)
{
    int len = finish - start + 1;
    if (start % 2 == 0)
    {
        if (finish % 2 == 0)
            return len / 2 + 1;
        else return len / 2;
    }
    else return len / 2;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int a, b, c, L;
    scanf("%d%d%d%d", &a, &b, &c, &L);
    i64 answer = 0;
    fore(x, a, a + L)
    {
        int x1 = x - b - c + 1;
        int x2 = L - (x - a);
        if (x1 > x2)
            continue;
        int y1 = c - x - b + 1;
        int y2 = x + c - b - 1;
        if (y1 > y2)
            continue;
        /*int x_even = get(x1, x2);
        int x_odd = x2 - x1 + 1 - x_even;
        int y_even = get(y1, y2);
        int y_odd = y2 - y1 + 1 - y_even;
        printf("x_even = %d x_odd = %d y_even = %d y_odd = %d\n", x_even, x_odd, y_even, y_odd);
        i64 to_add = (i64)x_even * y_even + (i64)x_odd * y_odd;
        cout << to_add << endl;
        answer += to_add;*/
        printf("x = %d x1 = %d x2 = %d y1 = %d y2 = %d\n", x, x1, x2, y1, y2);
        for (int x = x1; x <= x2; x++)
        {
            int lower = max(y1, -x);
            int upper = min(x, y2);
            if (lower > upper)
                continue;
            int y_even = get(lower, upper);
            if (x % 2 == 0)
                answer += y_even;
            else answer += upper - lower + 1 - y_even;
        }
    }
    cout << answer;
}
