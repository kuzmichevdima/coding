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

const i64 inf = 1e18;
const int maxn = 200005;

int order[maxn];
vi interest[5];
int n, k, b, c;

inline i64 get_cost(int start, int finish)
{
    int delta = finish - start;
    return (i64)(delta / 5) * b + (delta % 5) * c;
}

int T;

struct cmp
{
    bool operator()(int x, int y)
    {
        return get_cost(x, T) < get_cost(y, T);
    }
};

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &k, &b, &c);
    if (5 * c < b)
        b = 5 * c;
    forn(i, n)
    {
        int t;
        scanf("%d", &t);
        order[i] = t;
        forn(r, 5)
        {
            int tmp = (t + r >= 0 ? (t + r) % 5 : (5 - (-t -r) % 5) % 5);
            //printf("t + r = %d tmp = %d\n", t + r, tmp);
            interest[tmp].pb(t + r);
        }
    }
    sort(order, order + n);
    i64 answer = inf;
    forn(r, 5)
    {
        sort(interest[r].begin(), interest[r].end());
        int pointer = 0;
        multiset <int, cmp> Q;
        i64 cur_sum = 0;
        forn(i, interest[r].size())
        {
            T = interest[r][i];
            while(pointer < n && order[pointer] <= T)
            {
                Q.insert(order[pointer]);
                cur_sum += get_cost(order[pointer], T);
//                cout << "cur _sum = " << cur_sum << endl;
                if ((int)Q.size() > k)
                {
                    int x = *Q.rbegin();
                    Q.erase(Q.find(x));
                    cur_sum -= get_cost(x, T);
                }
                pointer++;
            } 
  //          cout << "T = " << T << " cur_sum  = " << cur_sum << endl;
            assert((int)Q.size() <= k);
            if ((int)Q.size() == k)
                answer = min(answer, cur_sum);
            if (i + 1 != (int)interest[r].size())
                cur_sum += (i64)(interest[r][i + 1] - interest[r][i]) / 5 * b * Q.size();
        }

    }
    cout << answer;
}
