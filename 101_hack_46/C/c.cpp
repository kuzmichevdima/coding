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

struct vertex {
	int next[26];
	vi numbers;
	int p;
	char pch;
	int link;
	int go[26];
};

const int maxn = 2e6+5;
 
vertex t[maxn];
int sz;
int cost[maxn];
 
void init() {
	t[0].p = t[0].link = -1;
	memset (t[0].next, 255, sizeof t[0].next);
	memset (t[0].go, 255, sizeof t[0].go);
	sz = 1;
}
 
void add_string (const string & s, int num) {
	int v = 0;
	for (size_t i=0; i<s.length(); ++i) {
		int c = s[i]-'a';
		if (t[v].next[c] == -1) {
			memset (t[sz].next, 255, sizeof t[sz].next);
			memset (t[sz].go, 255, sizeof t[sz].go);
			t[sz].link = -1;
			t[sz].p = v;
			t[sz].pch = c;
			t[v].next[c] = sz++;
		}
		v = t[v].next[c];
	}
	t[v].numbers.pb(num);
}
 
int go (int v, int c);
 
int get_link (int v) {
	if (t[v].link == -1) {
		if (v == 0 || t[v].p == 0)
			t[v].link = 0;
		else
			t[v].link = go (get_link (t[v].p), t[v].pch);
    }
	return t[v].link;
}
 
int go (int v, int c) {
	if (t[v].go[c] == -1) {
		if (t[v].next[c] != -1)
			t[v].go[c] = t[v].next[c];
		else
			t[v].go[c] = v==0 ? 0 : go (get_link (v), c);
    }
	return t[v].go[c];
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    init();
    int n;
    scanf("%d", &n);
    forn(j, n) {
        string s;
        cin >> s;
//        cout << "s = " << s << endl;
        add_string(s, j);
    }
    forn(j, n)
        scanf("%d", &cost[j]);
    int q;
    scanf("%d", &q);
    i64 minn = 0;
    i64 maxx = 0;
    forn(query, q) {
        int L, R;
        scanf("%d%d", &L, &R);
        string s;
        cin >> s;
        int cur = 0;
        i64 sum = 0;
        for (char c : s) {
            cur = go(cur, (int)(c - 'a'));
            //printf("cur = %d\n", cur);
            int tmp = cur;
            while(tmp != 0) {
                for (int x : t[tmp].numbers) {
                    if (x >= L && x <= R)
                        sum += cost[x];
                    //printf("%c x = %d sum = %lld\n", c, x, sum);
                }
                tmp = get_link(tmp);
            }
        }
        if (query == 0 || sum > maxx)
            maxx = sum;
        if (query == 0 || sum < minn)
            minn = sum;
    }
    cout << minn << " " << maxx;
}
