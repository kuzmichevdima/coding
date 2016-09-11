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

const int A = 1e5+1;
const int MOD = 1e9+7;
const int maxn = 1e5+5;

map <string, int> M;
vector <i64> counts;
vi hashes;
int n;
string s;
i64 p[maxn];

int get_hash(string s) {
    i64 res = 0;
    forn(i, s.length())
        res += p[(int)s.length() - i - 1] * s[i];
    return res % MOD;
}

void prepare() {
    p[0] = 1;
    fore(j, 1, n)
        p[j] = p[j - 1] * A % MOD;
    forn(i, n) {
        string cur = s.substr(i, 1);
        for (int j = i, right_bound = i; j >= 0 && right_bound < n; j--, right_bound++) if (s[j] == s[right_bound]) {
            M[cur]++;
            if (j > 0)
                cur = s[j - 1] + cur + s[j - 1];
        }
        else break;
        cur = s.substr(i, 2);
        for (int j = i, right_bound = i + 1; j >= 0 && right_bound < n; j--, right_bound++) if (s[j] == s[right_bound]) {
            M[cur]++;
            if (j > 0)
                cur = s[j - 1] + cur + s[j - 1];
        }
        else break;

    }
    for (auto & elem : M) {
        hashes.pb(get_hash(elem.fi));
        counts.pb(counts.empty() ? elem.se : counts.back() + elem.se);
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int q;
    scanf("%d%d", &n, &q);
    cin >> s;
    prepare();
    forn(query, q) {
        i64 num;
        cin >> num;
        if (num > counts.back())
            printf("-1\n");
        else {
            int pos = lower_bound(counts.begin(), counts.end(), num) - counts.begin();
            printf("%d\n", hashes[pos]);
        }
    }
}
