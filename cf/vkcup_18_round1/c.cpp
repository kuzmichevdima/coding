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
#include <unordered_map>

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

const int BITS = 30;

unordered_map<int, int> cnt[BITS + 1];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    vi a(n);
    forn(i, n) {
        scanf("%d", &a[i]);
    }
    forn(i, n) {
        int x;
        scanf("%d", &x);
        int part = 0; 
        for (int j = BITS; j >= 0; --j) {
            if (x & (1 << j))
                part |= (1 << j);
            cnt[j][part]++;
        }
    }
    //multiple elements?
    forn(i, n) {
        int cur = 0;
        for (int j = BITS; j >= 0; j--) {
            if (a[i] & (1 << j))
                cur |= (1 << j);
            auto find_res = cnt[j].find(cur);
            if (find_res == cnt[j].end() || !find_res->se) {
                cur ^= (1 << j);
            }
        }
        int x = cur;
        printf("%d ", x ^ a[i]);
        int part = 0;
        for (int j = BITS; j >= 0; --j) {
            if (x & (1 << j))
                part |= (1 << j);
            cnt[j][part]--;
        }
    }
}

