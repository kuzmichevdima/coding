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

struct Vector {
    int x, y;
    Vector (int x, int y) : x(x), y(y) {}
};

int main() {
    int n;
    scanf("%d", &n);
    double my_pi = -2 * atan2(-1.0, 0.0);
    forn(i, n) {
        int p, x, y;
        scanf("%d%d%d", &p, &x, &y);
        int d2 = (x - 50) * (x - 50) + (y - 50) * (y - 50);
        //printf("d2 = %d\n", d2);
        printf("Case #%d: ", i + 1);
        if (d2 > 2500) {
            printf("white\n");
            continue;
        }
        Vector u(0, 50);
        Vector v(x - 50, y - 50);
        // printf("x = %d y = %d u.x = %d u.y = %d %.10lf\n", x, y, u.x, u.y, my_pi);
        //printf("x = %d y = %d\n", x, y);
        double angle = atan2(v.x * u.y - v.y * u.x, v.x * u.x + v.y * u.y);
        //printf("%.10lf\n", angle);
        if (angle < 0)
            angle = 2 * my_pi + angle;
        //printf("%.10lf\n", angle);
        if (angle <= my_pi * p / 50)
            printf("black\n");
        else printf("white\n");
    }
}

