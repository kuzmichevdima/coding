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

const int limit = 1e6;

bool is_prime[limit + 5];
vi primes;
bool good_prime[limit + 5];

void sieve()
{   
    fore(i, 2, limit)
        is_prime[i] = true;
    fore(i, 2, limit)
        if (is_prime[i])
        {
            for (int j = 2 * i; j <= limit; j += i)
                is_prime[j] = false;
            primes.push_back(i);
        }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    sieve();
    /*forn(j, 20)
        printf("%d\n", primes[j]);
    exit(0);*/
    forn(j, primes.size())
        good_prime[j] = primes[j] % 4 == 1;
    forn(t, T)
    {
        int n;
        scanf("%d", &n);
        bool found = false;
        for (int j = 0; primes[j] * primes[j] <= n; j++)
            if (n % primes[j] == 0)
            {
                if (good_prime[j])
                {
                    found = true;
                    break;
                }
                while(n % primes[j] == 0)
                {
                    n /= primes[j];       
                }   
            }
//        printf("n = %d\n", n);
        if (n != 1 && n % 4 == 1)
            found = true;
        if (found)
            printf("YES\n");
        else printf("NO\n");
    }
}

