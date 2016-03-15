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
#include <stack>

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

const int maxn = 1e5 + 5;

int a[maxn];
int left_bound[maxn];
int right_bound[maxn];
int b[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, Q;
/*    n = 1e5;
    Q = 100;
    freopen("inp", "w", stdout);
    printf("%d %d\n", n, Q);
    forn(j, n)
        printf("%d ", rand() % (int)(1e8));
    printf("\n");
    forn(j, Q)
    {
        int x, y;
        x = rand() % n + 1;
        y = rand() % n + 1;
        if (x > y)
            swap(x, y);
        printf("%d %d\n", x, y);
    }
    exit(0);*/
    scanf("%d%d", &n, &Q);
    forn(j, n)
        scanf("%d", &b[j]);
    forn(j, n - 1)
    {
        a[j] = abs(b[j] - b[j + 1]);
     //   printf("a[%d] = %d\n", j, a[j]);
    }
    forn(it, Q)
    {
        int L, R;
        scanf("%d%d", &L, &R);
        R -= 2;
        L--;
//        printf("L = %d R = %d\n", L, R);
        stack <int> st;
        fore(pos, L, R)
        {
            //while(!st.empty() && a[st.top()] < a[pos])
            while(!st.empty() && a[st.top()] <= a[pos])
                st.pop();
            left_bound[pos] = (st.empty() ? L : st.top() + 1);
  //          printf("left_bound[%d] = %d\n", pos, left_bound[pos]);
            st.push(pos);
        }
        while(!st.empty())
            st.pop();
        for (int pos = R; pos >= L; pos--)
        {
            while(!st.empty() && a[st.top()] < a[pos])
                st.pop();
            right_bound[pos] = (st.empty() ? R : st.top() - 1);
    //        printf("right_bound[%d] = %d\n", pos, right_bound[pos]);
            st.push(pos);
        }
        i64 ans = 0;
        fore(pos, L, R)
        {
            //int len = right_bound[pos] - left_bound[pos] + 1;
            ans += (i64)a[pos] * (pos - left_bound[pos] + 1) * (right_bound[pos] - pos + 1);
        }
        cout << ans << endl;
     //   exit(0);
    }
}
