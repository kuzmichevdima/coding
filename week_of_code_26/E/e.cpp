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

int gcd(int x, int y) {
    return x == 0 ? y : gcd(y % x, x);
}

int main() {
    fore(n, 4, 1000) {
        int ans = 0;
        int bad = 0;
        fore(a, 1, n - 1) {
            fore(b, a + 1, n - 1) {
                bool ok = false;
                fore(x, 1, n / a) {
                    if (n - x * a != 0 && (n - x * a) % b == 0) {
                        ok = true;
                        break;
                    }
                }
                bool tmp = (n % a == 0 || n % b == 0);
                printf("%d %d ok = %d tmp = %d\n", a, b, ok, tmp);
                assert(ok == (n % gcd(a, b) == 0 && (!tmp || a * b / gcd(a, b) < n)));
                continue;
                if (ok) {
                    printf("%d %d\n", a, b);
                    assert(n % gcd(a, b) == 0 && (!tmp || a * b / gcd(a, b) < n));
                    //printf("a = %d b = %d\n", a, b);
                    ans++;
                } else {
                    //printf("%d %d\n", a, b);
                    //assert((n % gcd(a, b) == 0) == (a * b / gcd(a, b) >= n));
                }/*if (n % gcd(a, b) == 0) {
                    printf("bad %d %d\n", a, b);
                    assert(a * b / gcd(a, b) >= n);
                    bad++;
                }*/
/*                bool tmp = (n % gcd(a, b) == 0 && gcd(a, b) != 1);
                if (ok != tmp) {
                    printf("fail %d %d\n", a, b);
                    assert(false);
                }*/
                //assert(ok == (n % gcd(a, b) == 0 && gcd(a, b) != 1));
    /*            if (ok != (n % gcd(a, b)  == 0)) {
                    printf("fail %d %d\n", a, b);
                    assert(false);
                }*/
            }
        }
        printf("n = %d ans = %d bad = %d\n", n, ans, bad);
    }
}
