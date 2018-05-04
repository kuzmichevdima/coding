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

struct Triple {
    int first, second, third;
    Triple(int first_, int second_, int third_) : first(first_), second(second_), third(third_) {}
};


int main() {
    int n;
    scanf("%d", &n);
    if (n == 1) {
        printf("1\n0 0 1");
        exit(0);
    }
    if (n == 2) {
        printf("2\n 1 1 0\n0 0 2");
        exit(0);
    }
    vector <Triple> v;
    v.pb(Triple(0, 2, 1));
    v.pb(Triple(1, 0, 2));
    v.pb(Triple(2, 1, 0));
    int n1 = n;
    fore(n, 3, n1 - 1) {
        if (n % 3 == 0) {
            for (auto & e : v)
                e.first++;
        } else if (n % 3 == 1) {
            for (auto & e : v)
                e.third++;
            v.insert(v.begin(), Triple(0, n + 1, 0));
        } else {
            fore(pos, 1, v.size() / 2)
                v[pos].third++;
            fore(pos, v.size() / 2 + 1, (int)v.size() - 1)
                v[pos].first++;
            int new_first = v[v.size() / 2 + 1].fi - 1;
            auto insert_pos = v.begin() + (v.size() / 2 + 1);
            v.insert(insert_pos, Triple(new_first, n + 1 - new_first, 0));
            int new_third = v[1].third - 1;
            v[0] = Triple(0, n + 1 - new_third, new_third);
        }
        
    }
    printf("%d\n", (int)v.size());
    for (auto x : v)
        printf("%d %d %d\n", x.fi, x.se, x.third);
}

