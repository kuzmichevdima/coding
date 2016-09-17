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

#define ld long double

int main() {
    ld x, y, a, b;
    cin >> x >> y >> a >> b;
    ld n = (y * a - x * b) / (a * a + b * b);
    ld k = (x + n * b) / a;
    printf("%.10lf\n%.10lf", (double)k, (double)n);
}

