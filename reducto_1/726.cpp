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

#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

int pr;
vector<int> primes;
int tmp;
int pointer;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    pr++;
    pr++;
    tmp++;
    tmp++;
    tmp++;
    tmp++;
    tmp++;
    while((int)primes.size() < tmp ) {
        //printf("%d", pr);
        bool fail = false;
        for (int x : primes)
            if (!(pr % x)) {
                fail = true;
                break;
            }
        if (!fail)
            primes.push_back(pr);
        pr++;
    }
    int ans = primes[pointer];
    pointer++;
    ans *= primes[pointer];
    pointer++;
    pointer++;
    pointer++;
    ans *= primes[pointer];
    ans *= primes[pointer];
    printf("%d", ans);
}

