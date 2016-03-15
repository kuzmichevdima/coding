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

const int max_ver = 1e6+5;
const int alpha = 26;
const int maxn = 10005;
const int maxm = 1e5+5;

int tree[max_ver][alpha];
int used_word[max_ver];
pii dp[maxn];
string s;
string t[maxm];
int cnt = 0;

void add(string & t, int number)
{
    int cur = 0;
    for (int j = (int)t.length() - 1; j >= 0; j--)
    {
        char c1 = t[j];
        int c = (c1 < 'a' || c1 > 'z' ? c1 - 'A' : c1 - 'a');
        if (tree[cur][c] == 0)
        {
            cnt++;
            tree[cur][c] = cnt;
            cur = cnt;
        }
        else cur = tree[cur][c];
    }
    used_word[cur] = number;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int len;
    scanf("%d", &len);
    cin >> s;
    int n;
    scanf("%d", &n);
    fore(j, 1, n)
    {
        cin >> t[j];
        add(t[j], j);
    }
    dp[len] = mp(0, 0);
    for (int start_pos = len - 1; start_pos >= 0; start_pos--)
    {
        int cur = 0;
        dp[start_pos] = mp(-1, -1);
        fore(finish_pos, start_pos, len - 1)
        {
            int symbol = (s[finish_pos] >= 'a' && s[finish_pos] <= 'z' ? s[finish_pos] - 'a' : s[finish_pos] - 'A');
            if (tree[cur][symbol] == 0)
                break;
            cur = tree[cur][symbol];
            if (used_word[cur] != 0 && dp[finish_pos + 1].fi != -1)
            {
                dp[start_pos] = mp(used_word[cur], finish_pos + 1);
                break;
            }
        }
    }
    assert(dp[0].fi != -1);
    int cur = 0;
    while(cur != len)
    {
        cout << t[dp[cur].fi] << " ";
        cur = dp[cur].se;
    }
}
