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
#include <unordered_set>
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

const int maxn = 8005;

int n;
unordered_map<int, vi> pos;
int a[maxn];

int solve(int x, int y) {
    // printf("x = %d  y = %d\n", x, y);
    auto curx = pos[x].begin();
    auto cury = pos[y].begin();
    unordered_map<int, int> cnt;
    int valx = curx == pos[x].end() ? n : *curx;
    int valy = cury == pos[y].end() ? n : *cury;
    cnt[0] += min(valx, valy) + 1;
    int result = cnt[0] * (cnt[0] - 1) / 2;
    int balance = 0;
    while(valx != n || valy != n) {
        int was;
        if (valx < valy) {
            balance--;
            ++curx;
            was = valx;
            valx = curx == pos[x].end() ? n : *curx; 
        } else {
            balance++;
            ++cury;
            was = valy;
            valy = cury == pos[y].end() ? n : *cury;
        }
        int len = min(valx, valy) - was;
        result += cnt[balance] * len + len * (len - 1) / 2;
        //printf("balance = %d result = %d\n", balance, result);
        cnt[balance] += len;
    }
    return result;
}

int ez(int x, int y) {
    int res = 0;
    forn(j, n) {
        int bal = 0;
        fore(i, j, n - 1) {
            if (a[i] == x)
                bal++;
            if (a[i] == y)
                bal--;
            if (bal == 0)
                res++;
        }
    }
    return res;   
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int m;
    scanf("%d%d", &n, &m);
    unordered_set<int> values;
    map<pair<int, int>, int> double_answers;
    forn(j, n) {
        scanf("%d", &a[j]);
        values.insert(a[j]);
        pos[a[j]].pb(j);
    }
    forn(j, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x > y)
            swap(x, y);
        if (!values.count(x))
            swap(x, y);
        if (x == y || !values.count(x)) {
            printf("%d\n", n * (n + 1) / 2);
            continue;
        }
        if (!values.count(y)) {
            y = 0;
        }
        if (!double_answers.count(mp(x, y))) {
            double_answers[mp(x, y)] = solve(x, y);
        }
        //int right = ez(x, y);
        printf("%d\n", double_answers[mp(x, y)]);
        //assert(right == double_answers[mp(x, y)]);

    }
    
}

