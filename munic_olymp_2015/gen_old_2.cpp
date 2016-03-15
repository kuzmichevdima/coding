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

#include "testlib.h"

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

#define YES_RAND 1
#define NO 0
#define YES_BEST 2
#define YES_WORST 3

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const int maxn = 2e5+5;
const int breaking_size = 26;
const int breaking_test[breaking_size] = {7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 5, 6, 7, 7, 7, 7, 7, 1, 1, 3, 3, 3, 3, 3, 3, 3};

bool dp[maxn][8][8];
int cnt[8];
vi a;
int test_type;

void print()
{
    printf("%d\n", (int)a.size());
    forn(j, (int)a.size() - 1)
        printf("%d ", a[j]);
    printf("%d\n", a.back());
    exit(0);
}


void process(int pos)
{
    fore(previ, 1, 7)
            fore(prevj, 1, 7)
                if (dp[pos - 1][previ][prevj])
                {
                    if (abs(previ - a[pos]) <= 1)
                        dp[pos][a[pos]][prevj] = true;
                    if (abs(prevj - a[pos]) <= 1)
                        dp[pos][previ][a[pos]] = true;
                    if (prevj == a[pos] && previ < 7)
                        dp[pos][previ + 1][prevj] = true;
                    if (prevj == a[pos] && previ > 1)
                        dp[pos][previ - 1][prevj] = true;
                    if (previ == a[pos] && prevj < 7)
                        dp[pos][previ][prevj + 1] = true;
                    if (previ == a[pos] && prevj > 1)
                        dp[pos][previ][prevj - 1] = true;
                }
}

void add(int x)
{
    a.pb(x);
    process((int)a.size() - 1);
}

int main(int argc, char * argv[]) {
    if (argc != 3)
    {
        cerr << "There should be 2 arguments";
        exit(0);
    }
    int n = atoi(argv[1]);
    if (strcmp(argv[2], "no") == 0)
        test_type = NO;
    else if (strcmp(argv[2], "yes_rand") == 0)
        test_type = YES_RAND;
    else if (strcmp(argv[2], "yes_worst") == 0)
        test_type = YES_WORST;
    else if (strcmp(argv[2], "yes_best") == 0)
        test_type = YES_BEST;
    else
    {
        cerr << "invalid second argument";
        exit(0);
    }
    registerGen(argc, argv, 0);
    a.pb(rnd.next(1, 7));
    fore(i, 1, 7)
        dp[0][a[0]][i] = dp[0][i][a[0]] = 1;
    while((int)a.size() < n || test_type == NO)
    {
        int pos = a.size();
        if (a.back() == 7 && rnd.next(1, 8) == 1 && (int)a.size() + 100 < n)
        {
            forn(j, breaking_size)
                add(breaking_test[j]);
            continue;
        }
        fore(next, 1, 7)
        {
            cnt[next] = 0;
            fore(previ, 1, 7)
                fore(prevj, 1, 7) if (dp[pos - 1][previ][prevj])
                {
                    if (abs(previ - next) <= 1 || abs(prevj - next) <= 1)
                        cnt[next]++;
                }
        }
        if (pos >= n - 1 && test_type == NO)
        {
            fore(i, 1, 7)
                if (cnt[i] == 0)
                {
                    a.pb(i);
                    print();
                }
        }
        bool fail = true;
        fore(i, 1, 7)
            if (cnt[i] > 0)
                fail = false;
        if (fail)
        {
                        print();
        }

        if (test_type == YES_RAND || test_type == NO)
        {
            while(true)
            {
                int best = rnd.next(1, 7);
                if (cnt[best] > 0)
                {
                    a.pb(best);
                    break;
                }
            }
        }
        else if (test_type == YES_BEST)
        {
            int best = -1;
            forn(it, 50)
            {
                int j = rnd.next(1, 7);
                if (best == -1 || cnt[j] > cnt[best])
                    best = j;
            }
            a.pb(best);
        }
        else if (test_type == YES_WORST || test_type == NO)
        {
            int worst = -1;
            forn(it, 50)
            {
                int j = rnd.next(1, 7);
                if (cnt[j] > 0 && (worst == -1 || cnt[j] < cnt[worst]))
                    worst = j;
            }
            if (worst == -1)
                worst = 1;
            a.pb(worst);
        }
        process(pos);
    }
    print();
}

