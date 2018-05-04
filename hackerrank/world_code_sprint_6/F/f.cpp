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

const int maxn = 305;

int chosen[maxn];
bool usedy[maxn];
bool usedz[maxn];
int max_sz;
int ans[maxn];
int n, limit;

void go(int i, int sz = 0) {
    if (sz + n - i + 1 <= max_sz)
        return;
    if (n + 1 - sz == limit) {
        max_sz = sz;
        memcpy(ans, chosen, sizeof(chosen));
        return;
    }
    fore(j, 0, n - i) {
        if (!usedy[j] && !usedz[n - i - j]) {
            chosen[i] = j;
            usedy[j] = true;
            usedz[n - i - j] = true;
//            printf("i = %d j = %d is chosen (marked %d and %d)\n", i, j, j, n - i - j);
            go(i + 1, sz + 1);
            usedy[j] = false;
            usedz[n - i - j] = false;
        }
    }
    chosen[i] = -1;
    go(i + 1, sz);
}

int main() {
//    for (n = 1; n <= 12; n++) {
    max_sz = 0;
    scanf("%d", &n);
    limit = (n - 1) / 3 + 1;
    go(0);

    assert(n + 1 - max_sz == limit);
    printf("n = %d size is %d\n", n, max_sz);
    forn(i, n + 1) {
        if (ans[i] == -1)
            printf("%d is skipped\n", i);
        else printf("%d %d %d\n", i, ans[i], n - i - ans[i]);
    }

}
