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

const int alpha = 26;

struct node
{
	int len, link;
	int next[alpha];
	bool cloned;
	int first_pos;
};
const int maxn = 1e4;

node a[maxn * 2 + 5];
int sz, last;

void init()
{
	last = 0;
	a[last].len = 0;
	a[last].link = -1;
	a[last].cloned = false;
	forn(j, alpha)
		a[last].next[j] = -1;
	sz = 1;
}

inline void addLetter(int letter)
{
	sz++;
	int cur = sz - 1;
	a[cur].len = a[last].len + 1;
	a[cur].cloned = false;
	a[cur].first_pos = a[cur].len - 1;
	forn(j, alpha)
		a[cur].next[j] = -1;
	int p = last;
	while((p != -1) && (a[p].next[letter] == -1))
	{
		a[p].next[letter] = cur;
		p = a[p].link;
	}
	if (p == -1)
	{
		a[cur].link = 0;
	}
	else
	{
		int q = a[p].next[letter];
		if (a[q].len == a[p].len + 1)
			a[cur].link = q;
		else
		{
			sz++;
			int clone = sz - 1;
			a[clone].len = a[p].len + 1;
			a[clone].link = a[q].link;
			a[clone].cloned = true;
			a[clone].first_pos = a[q].first_pos;
			memcpy(a[clone].next, a[q].next, sizeof(a[clone].next));
			while((p != -1) && (a[p].next[letter] == q))
			{
				a[p].next[letter] = clone;
				p = a[p].link;
			}
			a[q].link = a[cur].link = clone;
		}
	}
	last = cur;
}

vi edges[maxn * 2 + 5];
int cnt, first_occur, last_occur;

void dfs(int state)
{
	if (!a[state].cloned)
	{
		cnt++;
		first_occur = min(first_occur, a[state].first_pos);
		last_occur = max(last_occur, a[state].first_pos);
	}
	forn(j, edges[state].size())
		dfs(edges[state][j]);
}



int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	string s;
	cin >> s;
	init();	
	forn(j, s.length())
		addLetter(s[j] - 'a');
	forn(j, sz)
		edges[a[j].link].pb(j);
	int answer = 0;
	fore(j, 1, sz - 1)
	{
		//printf("===============\n");
		//printf("j = %d\n", j);
		first_occur = s.length();
		last_occur = 0;
		cnt = 0;
		dfs(j);
		
		int upper = a[j].len;
		//printf("len = %d\n", a[j].len);
		if (cnt < 2)
			continue;
		
		upper = min(upper, first_occur + 1);
		upper = min(upper, last_occur - first_occur);
		int lower = a[a[j].link].len + 1;
		//printf("lower = %d upper = %d\n", lower, upper);
		if (lower <= upper)
		{
			answer += (upper - lower + 1);
			//printf("+= %d\n", upper - lower + 1);
		}
		
	}
	printf("%d", answer);
	return 0;
}