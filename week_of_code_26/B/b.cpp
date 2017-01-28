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
    int n;
    scanf("%d", &n);
    int ans = 0;
    int max_digit_sum = 0;
    for (int d = 1; d <= n; d++)
        if (n % d == 0) {
            int digit_sum = 0;
            int y = d;
            while(y != 0) {
                digit_sum += y % 10;
                y /= 10;
            }
            if (digit_sum > max_digit_sum) {
                max_digit_sum = digit_sum;
                ans = d;
            }
        }
    printf("%d", ans);
}
