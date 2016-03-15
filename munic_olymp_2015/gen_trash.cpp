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
#define YES_TRASH 4

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const int maxn = 2e5+5;
const int trash_const = 7;

int n;
vi a;

void print()
{
    printf("%d\n", (int)a.size());
    forn(j, (int)a.size() - 1)
        printf("%d ", a[j]);
    printf("%d\n", a.back());
    exit(0);
}


int main(int argc, char * argv[]) {
    if (argc != 3)
    {
        cerr << "There should be 2 arguments";
        exit(0);
    }
        
    registerGen(argc, argv, 0);
    n = atoi(argv[1]);
    int flag = atoi(argv[2]);
    assert(flag == 0 || flag == 1); 
    forn(j, 5)
        a.pb(7);
    while((int)a.size() < n)
    {
        a.pb(6);
        if (rnd.next(1, 2) == 1)
        {
            a.pb(7);
            a.pb(6);
        }
        a.pb(5);
        a.pb(6);
        if (rnd.next(1, 2) == 1)
        {
            a.pb(7);
            a.pb(6);
        }

        a.pb(7);
    }

    a.pb(1);
    if (flag)
        forn(j, a.size())
            a[j] = 8 - a[j];
    print();
}

