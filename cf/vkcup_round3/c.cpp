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

#define ROOT 0

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const int maxn = 1e5 + 5;
const int maxvert = maxn * 61;
const int BITS = 60;

int sz[maxvert];
int trie[maxvert][2];
int anc[maxvert];

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
    int cnt = 1;
    i64 cur = 0;
    forn(i, n) {
        i64 b;
        cin >> b; 
        cur ^= b;
        int vert = ROOT;
        //printf("\nb = %lld cnt = %d\n", b, cnt);
        for (int j = BITS - 1; j >= 0; --j) {
            bool bit = (1LL << j) & b;
            //printf("%d", bit);
            if (trie[vert][bit] == 0) {
                trie[vert][bit] = cnt;
                anc[cnt] = vert;
                vert = cnt;
                ++cnt;
            } else {
                vert = trie[vert][bit];
            }
            sz[vert]++;
        }
    }
    //cout << cnt << " " << BITS * n << endl;
    vector<i64> ans;
    forn(i, n - 1) {
        cout << i << " " << cur << endl;
        int vert = ROOT;
        vi best;
        vi best_bit;
        for (int j = BITS - 1; j >= 0; --j) {
            bool bit = (1LL << j) & cur;
            int next = trie[vert][0];
            int tmp = trie[vert][1];
            if (tmp != 0 && sz[tmp] > 0 && bit == 1) {
                best.pb(tmp);
                best_bit.pb(j);
            }
            //printf("vert = %d tmp = %d bit = %d\n", vert, tmp, bit);
            if (next == 0 || sz[next] == 0)
                break;
            vert = next;
        }
        i64 max_tmp = -1e9;
        int max_vert = -1;
        forn(x, best.size()) { 
            vert = best[x];
            i64 nnew = 0;
            for (int j = BITS - 1; j >= best_bit[x]; --j)
                if ((1LL << j) & cur)
                    nnew |= (1LL << j);
            for (int j = best_bit[x] - 1; j >= 0; --j) {
                bool bit = (1LL << j) & cur;
                int need_bit = !bit;
                int next = trie[vert][need_bit];
                //printf("vert = %d j = %d bit = %d cur = %lld next = %d\n", vert, j, bit, cur, next);
                bool fin = (next == 0 || sz[next] == 0) ? !need_bit : need_bit;
                if (fin == 1)
                    nnew |= (1LL << j);
                vert = trie[vert][fin];
            }
            i64 tmp = nnew ^ cur;
            if (tmp >= cur)
                continue;
            if (tmp > max_tmp) {
                max_tmp = tmp;
                max_vert = vert;
            }
        }
        if (max_vert == -1) {
            printf("No");
            exit(0);
        }
        forn(iter, BITS) {
            sz[max_vert]--;
            vert = anc[max_vert];
        }
        //cout << "nnew = " << nnew << " tmp = " << tmp << endl;
/*        if (tmp >= cur) {
            printf("No");
            exit(0);
        }*/
        ans.pb(max_tmp ^ cur);
        cur = max_tmp;
    }
    for (int i = n - 1; i >= 0; --i)
        cout << ans[i];
}

