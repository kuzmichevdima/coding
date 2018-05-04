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


const int maxn = 2e6+5;

int ans[maxn];
int n, q;


void print_odd(i64 shift) {
 //   cout << "print_odd" << shift << endl;
    shift %= (n / 2);
    for (int j = 1; j < n; j += 2)
        ans[(j + (shift * 2)) % n] = j;
}

void print_even(i64 shift) {
    //cout << "print_even" << shift << endl;
    shift %= (n / 2);
    for (int j = 0; j < n; j += 2)
        ans[(j + (shift * 2)) % n] = j;
}


int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    //int starttime = clock();
    scanf("%d%d", &n, &q);
    i64 even_shift = 0, odd_shift = 0;
    int swap_cnt = 0;
    forn(i, q) {
        int typ;
        scanf("%d", &typ);
        if (typ == 1) {
            int x;
            scanf("%d", &x);
            if (x < 0)
                x = n + x;
            if (x % 2 == 0) {
                odd_shift += x / 2;
                even_shift += x / 2;
            } else {
                odd_shift += x / 2 + 1;
                even_shift += x / 2;
                swap(odd_shift, even_shift);
                swap_cnt++;
            }
        } else {
            swap(odd_shift, even_shift);
            swap_cnt++;
        }
    }
    if (swap_cnt % 2 == 0) {
//        printf("case 1\n");
        print_even(even_shift);
        print_odd(odd_shift);
    } else {
        print_odd(even_shift);
        print_even(odd_shift);
        for (int j = 0; j < n; j += 2)
            swap(ans[j], ans[j + 1]);
    }
    forn(j, n)
        printf("%d ", ans[j] + 1);
}
