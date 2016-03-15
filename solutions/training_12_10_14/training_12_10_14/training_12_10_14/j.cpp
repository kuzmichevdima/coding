#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <queue>
#include <memory.h>
#include <cmath>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)
#define all(x) (x).begin(), (x).end()
#define se second
#define fi first
#define mp make_pair
#define pb push_back
#define op operator
typedef vector <int> vi;
typedef pair<int, int> pii;
typedef long long i64;

int n, m, t;
int is_t[100100];
int term[100100];
vector<int> g[100100];
vector<char> c[100100];
string s;
int r[100100];

struct state {
	int len, link;
	bool term;
	map<char,int> next;
};

const int MAXLEN = 100100;
state st[MAXLEN * 2];
int sz, last;

void initSA() {
	sz = last = 0;
	st[0].len = 0;
	st[0].link = -1;
	term[0] = false;
	++sz;
}

void extendSA(char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	int p;
	for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
		st[p].next[c] = cur;
	if (p == -1)
		st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len)
			st[cur].link = q;
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			st[clone].next = st[q].next;
			st[clone].link = st[q].link;
			for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}

void destroySA() {
	for (int i = 0; i < sz; i++)
		st[i].next.clear(), st[i].term = false;
}

void buildSA(string &s) {
	initSA();
	for (int i = 0; i < (int)s.length(); i++)
		extendSA(s[i]);
}

int used[200100];

bool dfs(int v1, int v2, int col) {
	used[v1] = col;
	r[v1] = v2;
	for (int i = 0; i < (int)g[v1].size(); i++) {
		int to1 = g[v1][i];
		int cc = c[v1][i];
		if (st[v2].next.find(cc) == st[v2].next.end())
			return false;
		int to2 = st[v2].next[cc];
		if (used[to1] != col) {
			if (!dfs(to1, to2, col))
				return false;
		} else {
			if (r[to1] != to2)
				return false;
		}
	}
	return true;
}

bool solve(int test) {
	for (int i = 0; i < t; i++) {
		cin >> term[i];
		term[i]--;
		is_t[term[i]] = test;
	}
	//cerr << n << ' '<< m << ' '<< t << endl;
	for (int i = 0; i < m; i++) {
		int u, v;
		char cc;
		cin >> u >> v >> cc;
		//cerr << u << ' ' << v << ' ' << cc << endl;
		u--, v--;
		g[u].push_back(v);
		c[u].push_back(cc);
	}
	cin >> s;
	//cerr << s << endl;
	for (int i = 0; i < n; i++)
		r[i] = -1;
	buildSA(s);

	bool res = dfs(0, 0, test);
	int cur = last;
	while (true) {
		st[cur].term = true;
		if (cur == 0)
			break;
		cur = st[cur].link;
	}
	for (int i = 0; i < t; i++)
		if (!st[r[term[i]]].term)
			res = false;

	for (int i = 0; i < n; i++)
		g[i].clear(), c[i].clear();
	destroySA();

	return res;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int cnt = 0;
	while (true) {
		cnt++;
		if (!cin >> n >> m >> t)
			return 0;
		//if (n == 0 && m == 0 && t == 0)
	//		return 0;
		cout << "Automaton " << cnt << " is ";
		if (solve(cnt))
			cout << "a machinegun.\n";
		else
			cout << "not a machinegun.\n";
	}
	return 0;
}