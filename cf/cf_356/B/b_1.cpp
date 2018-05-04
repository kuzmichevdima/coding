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

const int limit = 1e5;
const int limit3 = 100;

pii ans[limit * 10 + 5];

typedef pair<int, i64> mypair;

map <pair<i64, i64> , mypair> ma;

mypair f(i64 M, i64 p) {
    //cout << "M = " << M << " p = " << p << " " << endl;
    p = min(p, (i64)pow(M, 1.0 / 3));
    if (ma.find(mp(M, p)) != ma.end())
        return ma[mp(M, p)];
    if (p == 1 || M == 0)
        return mp(M, M);
//    while(p * p * p > M)
  //      p--;
    i64 p3 = p * p * p;
    mypair reduced = f(M % p3, p - 1);
    i64 kr = M / p3;
    mypair result = mp(reduced.fi + kr, reduced.se + p3 * kr);
    if (true) {
        mypair reduced = f(p3 - 1, p - 1);
        mypair nnew = mp(reduced.fi + (kr - 1), reduced.se + p3 * (kr - 1));
        result = max(result, nnew);
    }
    //i64 psharp3 = (p - 1) * (p - 1) * (p - 1);
    //i64 tmp = M - psharp3;
    //if (tmp < p3) {
 //   auto nnew = f(p3 - 1, p - 1);
   // result = max(result, nnew);
    //}
  //  cout << "M = " << M << " p = " << p << " " << result.fi << " " << result.se << endl;
    return ma[mp(M, p)] = result;
}

int main() {
    //fore(j, 1, 10 * limit) {
    fore(j, 1, limit) {
        int p = limit3;
        int L = j;
        int cnt = 0;
        while(L > 0) {
            while(p * p * p > L)
                p--;
            L -= p * p * p;
            cnt++;
        }
//        printf("%d %d\n", j, cnt);
        ans[j] = max(ans[j - 1], mp(cnt, j));
    }
    i64 M;
    cin >> M;
    //cout << "\nez ans " << ans[M].fi << " " << ans[M].se << endl;
    mypair answer = f(M, limit);
    cout << answer.fi << " " << answer.se;
/*    i64 opt = 0;
    i64 ans = 0;
    fore(i, 1, limit) {
        i64 cur = opt;
        i64 pow3 = (i64)i * i * i;
        i64 powi1 = (i64)(i + 1) * (i + 1) * (i + 1);
        i64 new_opt = 0;
        while(cur < powi1 && cur <= M) {
            new_opt = cur;
            ans++;
            cur += pow3;
        }
        ans--;
        opt = new_opt;
        if (cur > M)
            break;
        cout << "i = " << i << "opt = " << opt << endl;
    }
    cout << ans << " " << opt;*/
    /*i64 M;
    cin >> M;
    int cc = 0;
    pair <int, i64> best;
    for (i64 last = limit; last >= 1; last--) {
        i64 pow3 = last * last * last;
        if (pow3 > M)
            continue;
        i64 tmp = M - pow3;
        if (tmp > 10 * limit)
            break;
        i64 last13 = (last + 1) * (last + 1) * (last + 1);
        fore(num, 1, 7) {
            i64 taken = pow3 * num;
            i64 left = min(M - taken, last13 - taken - 1);
            if (taken >= last13 || left < 0 || left > 10 * limit || left >= pow3)
                continue;
            int nnew = ans[left].fi + num;
            i64 X = ans[left].se + pow3 * num;
            best = max(best, mp(nnew, X));
        }
    }
    cout << best.fi << " " << best.se;*/
}

