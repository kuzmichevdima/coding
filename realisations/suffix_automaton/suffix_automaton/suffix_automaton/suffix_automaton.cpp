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

struct node
{
	int len, link;
	int next[26];
};
const int maxn = 1e5;

node a[maxn * 2 + 5];
int sz, last;

void init()
{
	last = 0;
	a[last].len = 0;
	a[last].link = -1;
	forn(j, 26)
		a[last].next[j] = -1;
	sz = 1;
}

inline void addLetter(int letter)
{
	sz++;
	int cur = sz - 1;
	a[cur].len = a[last].len + 1;
	forn(j, 26)
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
	vi answer;
	answer.pb(1);
	fore(j, 1, sz - 1)
	{
		answer.pb(a[j].len - a[a[j].link].len);
	}
	sort(all(answer));
	forn(j, answer.size())
		printf("%d ", answer[j]);
	return 0;
}