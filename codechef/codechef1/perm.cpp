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

int n, k;
set <vi> s;

void go(vi v)
{
    if (s.find(v) == s.end())   
    {
        s.insert(v);
        forn(start, n - k + 1)
        {
            vi a = v;
            int tmp = a[start + k - 1];
            for (int p = start + k - 1; p > start; p--)
                a[p] = a[p - 1];
            a[start] = tmp;
            go(a);
        }
    }
    else return;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(T, tests)
    {
        scanf("%d%d", &n, &k);
        //printf("k = %d\n", k);
        vi a(n);
        forn(j, n)
            a[j] = n - j;
            /*scanf("%d", &a[j]);
        vi b(n);
        forn(j, n)
            scanf("%d", &b[j]);*/
        s.clear();
        go(a);
        int number = 0;
        bool found = false;
        for (auto iter = s.begin(); iter != s.end(); iter++)
        {
            //printf("number = %d\n", number);
            number++;
            //vi v = *iter;
           /* if (v == b)
            {
                printf("%d\n", number);
                found = true;
                break;
            }*/
  /*          printf("number = %d\n", number);
            forn(j, n)
                printf("%d ", v[j]);
            printf("\n");*/
        }
        printf("n = %d k = %d number = %d\n", n, k, number);
        if (!found)
            printf("-1\n");
    }
}

