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

char get(i64 x, int level) {
    i64 left_len = (1LL << (level - 1)) - 1;
    if (x <= left_len)
        return get(x, level - 1);
    if (x == left_len + 1) {
        return 'a';
    }
    char tmp = get(2 * left_len + 2 - x, level - 1);
    return tmp == 'a' ? 'c' : 'a';

}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int t;
    scanf("%d", &t);
    forn(test, t) {
        i64 x;
        cin >> x;
        printf("%c\n", get(x, 60));
    }
}

