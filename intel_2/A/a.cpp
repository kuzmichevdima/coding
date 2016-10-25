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

const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int ans[12];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    vector <string> v = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
    int sum = 0; 
    forn(j, 12) {
        ans[j] = sum % 7;
        sum += days[j];
    }
    /*string s1, s2;
    cin >> s1;
    int x = find(v.begin(), v.end(), s1) - v.begin();
    cin >> s2;
    int y = find(v.begin(), v.end(), s2) - v.begin();*/
    vector <int> add = {28, 30, 31};
    forn(x, 7)
        forn(y, 7) {
            bool my_ans = false;
            for (int a : add)
                if ((x + a) % 7 == y) {
                    my_ans = true;
                }
            bool his_ans = false;
            his_ans = y == x || y - x == 3 || y - x == 2 || (6-x)+y+1==3 || (6-x)+y+1==2;
            if (his_ans != my_ans)
                printf("%d %d my %d his %d\n", x, y, my_ans, his_ans);
            assert(his_ans == my_ans);
        }
}
