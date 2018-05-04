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

int main() {
    vi v;
    fore(i, 2, 100) {
        bool prime = true;
        for (int d = 2; d * d <= i; d++)
            if (i % d == 0) {
                prime = false;
                break;
            }
        if (prime)
            v.pb(i);
    }
    vi v1;
    v1.pb(2);
    v1.pb(3);
    v1.pb(5);
    v1.pb(7);
    forn(it, 4) {
        printf("%d\n", v1[it] * v1[it]);
        fflush(stdout);
        string s;
        cin >> s;
        if (s == "yes") {
            cout << "composite";
            fflush(stdout);
            exit(0);
        }
    }
    int cnt = 0;
    forn(it, 16) {
        printf("%d\n", v[it]);
        fflush(stdout);
        string s;
        cin >> s;
        if (s == "yes")
            cnt++;
    }
    if (cnt <= 1)
        cout << "prime";
    else cout << "composite";
    fflush(stdout);
/*    for (int d = 2; d <= 10; d++) {
        printf("%d\n", d);
        fflush(stdout);
        cin >> s;
        if (s == "
    }*/
}
