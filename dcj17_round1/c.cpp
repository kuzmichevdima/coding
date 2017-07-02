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

#include <message.h>
#include "todd_and_steven.h"
//#include "sample3.h"

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

const i64 mod = 1e9+7;

int main() {
    int work_nodes = NumberOfNodes() - 1;
    int id = MyNodeId();
    i64 even_len = GetStevenLength();
    i64 odd_len = GetToddLength();
    if (id == work_nodes) {
        vector<i64> v;
        forn(j, even_len)
            v.pb(GetStevenValue(j));
        forn(j, odd_len)
            v.pb(GetToddValue(j));
        sort(v.begin(), v.end());
        i64 right_ans = 0;
        for(i64 j = 0; j <  (i64)v.size(); ++j)
            right_ans = (right_ans + (v[j] ^ j)) % mod;
        cout << right_ans;
        /*int cur_even = 0;
        int cur_odd = 0;
        i64 ans = 0;
        while(cur_even < even_len || cur_odd < odd_len) {
            i64 even = cur_even < even_len ? GetStevenValue(cur_even) : inf;
            i64 odd = cur_odd < odd_len ? GetToddValue(cur_odd) : inf;
            if (even < odd) {
                //ans = (ans + even ^ (cur_even + cur_odd)) % mod;
                ans = (even ^ (cur_even + cur_odd) + ans) % mod;
                cur_even++;
            } else {
                //ans = (ans + odd ^ (cur_even + cur_odd)) % mod;
                ans = (odd ^ (cur_even + cur_odd) + ans) % mod;
                cur_odd++;
            }
        }
        cout << ans << endl;*/
    }
}

