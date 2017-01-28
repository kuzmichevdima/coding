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

vi primes;

bool check(int x) {
    for (int div : primes) {
        if (div >= x)
            break;
        if (x % div == 0) {
            return false; 
        }
    }
    return true;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int prime = 2; prime * prime <= m; prime++) {
        bool fail = false;
        for (int x : primes) {
            if (prime % x == 0) {
                fail = true;
                break;
            }
            if (x * x > prime)
                break;
        }
        if (!fail)
            primes.pb(prime);
    }
    int ans = 0;
    if (n <= 3 && m >= 5)
        ans++;
    fore(i, n / 6, m / 6) {
        if (i * 6 - 1 >= n && i * 6 + 1 <= m && check(i * 6 - 1) && check(i * 6 + 1)) {
            ans++;
        }
    }
    printf("%d", ans);
}
