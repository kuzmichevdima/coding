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
    int n, m;
    scanf("%d%d", &n, &m);
    if (n % 2 == 1)
        n = n / 2 + 1;
    else n = n / 2;
    if (m % 2 == 1)
        m = m / 2 + 1;
    else m = m / 2;
    printf("%d", n * m);
}

