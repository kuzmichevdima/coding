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

i64 get_sqrt(i64 D) {
    i64 start = 0;
    i64 finish = 1e9;
    while(start < finish) {
        i64 middle = (start + finish) / 2 + 1;
        if (middle * middle <= D)
            start = middle;
        else finish = middle - 1;
    }
    return start * start == D ? start : -1;
}

i64 n, a1, b1, c1;

void check(i64 x, i64 y, i64 z, i64 c) {
    if (y < 1 || y > n || z < 1 || z > n)
        return;
    if (x == y || y == z || x == z)
        return;
    if (x * x * x + y * y * y + z * z * z != c)
        return;
    cout << x << " " << y << " " << z << endl;
    exit(0);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    cin >> n >> a1 >> b1 >> c1;
    i64 a = (1 + n) * n / 2 - a1;
    i64 b = n * (n + 1) * (2 * n + 1) / 6 - b1;
    i64 c = n * n * (n + 1) * (n + 1) / 4 - c1;
//    cout << "a = " << a << " b = " << b << " c = " << c << endl;
    for (i64 x = 1; x <= n; x++) {
        i64 C = a * a - 2 * a * x + 2 * x * x - b;
        i64 B = -2 * a + 2 * x;
        i64 A = 2;
        i64 D = B * B - 4 * A * C;
      //  cout << x << " " << A << " " << B << " " << C << " " << D << endl;
        if (D < 0)
            continue;
        i64 sq = get_sqrt(D);
        if (sq == -1)
            continue;
        if (abs(-B + sq) % (2 * A) == 0) {
            i64 z1 = (-B + sq) / (2 * A);
            i64 y1 = a - x - z1;
            check(x, y1, z1, c);
        }
        if (abs(-B - sq) % (2 * A) == 0) {
            i64 z2 = (-B - sq) / (2 * A);
            i64 y2 = a - x - z2;
            check(x, z2, y2, c);
        }
    }
    assert(false);
}
