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

int K;
int symb_cnt[26];

inline bool check(set<int>::iterator iter, int pos) {
//    printf("check %d and %d\n", *iter, pos);
    return abs(*iter - pos) < K;

}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &K);
    string s;
    cin >> s;
    forn(pos, s.length())
        symb_cnt[s[pos] - 'a']++;
    forn(used, 26) {
    //    printf("========================\n");
        int cnt = 0;
        set <int> P, Q;
        bool fail = false;
        forn(pos, s.length()) {
            if (s[pos] < 'a' + used)
                P.insert(pos);
            else if (s[pos] == 'a' + used) {
                Q.insert(pos);
      //          printf("in Q %d\n", pos);
            }
        }
//        printf("used = %d sizes %d %d\n", used, (int)P.size(), (int)Q.size());
        fore(pos, K - 1, (int)s.length() - 1) {
  //          printf("pos = %d\n", pos);
            auto iter = P.upper_bound(pos);
            if (iter != P.begin()) {
                iter--;
                if (check(iter, pos))
                    continue;
            }
            iter = Q.upper_bound(pos);
            if (iter != Q.begin()) {
                iter--;
                if (check(iter, pos)) {
                    P.insert(*iter);
        //            printf("added %d\n", *iter);
                    cnt++;
                    continue;
                }
            }
       //     printf("failed\n");
            fail = true;
            break;
        }
        if (fail)
            continue;
        string ans = "";
        forn(c, used) {
            forn(it, symb_cnt[c])
                ans += ('a' + c);
        }
        forn(it, cnt)
            ans += ('a' + used);
        cout << ans;
        exit(0);
    }
}
