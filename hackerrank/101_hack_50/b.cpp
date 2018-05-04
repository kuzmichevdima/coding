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
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n;
        scanf("%d", &n);
        i64 total_give = 0;
        int give = 0;
        int take = 0;
        i64 sum = 0;
        int tmp = 0;
        forn(i, n) {
            tmp += i % 2;
            int x;
            scanf("%d", &x);
            sum += x;
            if (i % 2 == 0) {
                if (x % 2 == 0) {
                    //give++;
                    total_give += x - 2;
                } else {
                    if (x == 1)
                        take++;
                    else {
                        give++;
                        total_give += x - 3;
                    }
                }
            } else {
                if (x % 2 == 1) {
                    //give++;
                    total_give += x - 1;
                } else {
                    give++;
                    total_give += x - 2;
                }
            }
        }
        //printf("give = %d take =%d total_give = %lld sum = %lld tmp = %d\n", give, take, total_give, sum, tmp);
        int answer;
        if (sum % 2 != tmp % 2) {
            answer = -1;
        } else {
            if (take <= give) {
                answer = (take + give) / 2;
            } else {
                answer = give;
                take -= give;
                if (take > total_give)
                    answer = -1;
                else answer += take;
            }
        }
        printf("%d\n", answer);
    }
}

