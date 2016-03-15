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

const int maxn = 1e4 + 5;

int cnt[maxn];
int c_new[maxn];
int c[maxn];
int p[maxn];
int order_by_second[maxn];
string s;
int n;

void print(int sz)
{
	printf("sz = %d\np = (", sz);
	forn(j, n)
		printf("%d ", p[j]);
	printf(")\nc = (");
	forn(j, n)
		printf("%d ", c[j]);
	printf(")\n");
}

void suf_arr()
{
	memset(cnt, 0, sizeof(cnt));
	forn(j, n)
		cnt[s[j] - 'a']++;
	fore(j, 1, 25)
		cnt[j] += cnt[j - 1];
	for (int j = n - 1; j >= 0; j--)
		p[--cnt[s[j] - 'a']] = j;
	c[p[0]] = 0;
	int classes = 1;
	fore(j, 1, n - 1)
	{
		if (s[p[j]] != s[p[j - 1]])
		{
			classes++;
		}
		c[p[j]] = classes - 1;
	}
	print(1);
	int sz = 2;
	while(sz <= n)
	{
		forn(j, n)
		{
			order_by_second[j] = p[j] - sz / 2;
			if (order_by_second[j] < 0)
				order_by_second[j] += n;
		}
		memset(cnt, 0, sizeof(cnt));
		forn(j, n)
			cnt[c[order_by_second[j]]]++;
		fore(j, 1, n - 1)
			cnt[j] += cnt[j - 1];
		for (int j = n - 1; j >= 0; j--)
		{
			p[--cnt[c[order_by_second[j]]]] = order_by_second[j];
		}
		c_new[p[0]] = 0;
		int classes = 1;
		fore(j, 1, n - 1)
		{
			int t_prev = c[(p[j - 1] + sz / 2) % n];
			int t_cur = c[(p[j] + sz / 2) % n];
			if (t_prev != t_cur || c[p[j]] != c[p[j - 1]])
				classes++;
			c_new[p[j]] = classes - 1;
		}
		memcpy(c, c_new, sizeof(c_new));
		print(sz);
		sz *= 2;
	}

}

pair <string, int> tmp[maxn];
int right_ans[maxn];

void easy_sol()
{
	forn(j, n)
	{
		tmp[j].fi = "";
		int cur = j;
		forn(it, n)
		{
			tmp[j].fi += s[cur];
			cur++;
			if (cur == n)
				cur = 0;
		}
		tmp[j].se = j;
	}
	sort(tmp, tmp + n);
	forn(j, n)
		right_ans[j] = tmp[j].se;
	printf("right ans:\n");
	forn(j, n)
		printf("%d ", right_ans[j]);
	printf("\n");
}

int main()
{
	freopen("output.txt", "w", stdout);
	s = "";
	forn(j, 100)
		s += ('a' + rand() % 26);
	n = s.length();
	easy_sol();
	suf_arr();
	forn(j, n)
		assert(right_ans[j] == p[j]);
	printf("OK");
	return 0;
}