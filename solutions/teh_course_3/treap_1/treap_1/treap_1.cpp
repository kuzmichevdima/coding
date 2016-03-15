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

struct treap
{
	int data, y, sz;
	i64 sum;
	treap * l;
	treap * r;
	treap(int _x) : data(_x), sum(_x), y(rand()), sz(1), l(NULL), r(NULL) {}
};
typedef treap * pt;

inline i64 get_sum(pt & p)
{
	return (p == NULL ? 0 : p->sum);
}

inline int get_sz(pt & p)
{
	return (p == NULL ? 0 : p->sz);
}

inline void recalc(pt & p)
{
	if (p == NULL)
		return;
	p->sum = get_sum(p->l) + get_sum(p->r) + p->data;
	p->sz = get_sz(p->l) + get_sz(p->r) + 1;
}

void merge(pt & p, pt pl, pt pr)
{
	if (pl == NULL)
	{
		p = pr;
		return;
	}
	if (pr == NULL)
	{
		p = pl;
		return;
	}
	if (pl->y > pr->y)
	{
		p = pl;
		merge(p->r, p->r, pr);
	}
	else
	{
		p = pr;
		merge(p->l, pl, p->l);
	}
	recalc(p);
}

void split(pt p, int x0, pt & pl, pt & pr)
{
	if (p == NULL)
	{
		pl = pr = NULL;
		return;
	}
	int c = get_sz(p->l) + 1;
	if (x0 >= c)
	{
		pl = p;
		split(p->r, x0 - c, pl->r, pr);
	}
	else
	{
		pr = p;
		split(p->l, x0, pl, pr->l);
	}
	recalc(pl);
	recalc(pr);
}

pt root_odd, root_even;

pt even_part1, even_part2, even_part3, even;
pt odd_part1, odd_part2, odd_part3, odd;

int odd_l, odd_r, even_l, even_r;

inline void make_splits()
{
	split(root_even, even_r, even_part1, even_part2);
	split(even_part1, even_l - 1, even_part3, even);

	split(root_odd, odd_r, odd_part1, odd_part2);
	split(odd_part1, odd_l - 1, odd_part3, odd);
}

inline void make_swap()
{
	make_splits();

	merge(odd_part1, odd_part3, even);
	merge(root_odd, odd_part1, odd_part2);

	merge(even_part1, even_part3, odd);
	merge(root_even, even_part1, even_part2);
}

inline void get_sum()
{
	make_splits();
	i64 answer = get_sum(even) + get_sum(odd);
	printf("%lld\n", answer);

	merge(odd_part1, odd_part3, odd);
	merge(root_odd, odd_part1, odd_part2);

	merge(even_part1, even_part3, even);
	merge(root_even, even_part1, even_part2);
}

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int test_number = 0;
	while(true)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0)
			break;
		root_odd = root_even = NULL;
		test_number++;
		printf("Swapper %d:\n", test_number);
		fore(j, 1, n)
		{
			int x;
			scanf("%d", &x);
			if (j % 2 == 0)
			{
				merge(root_even, root_even, new treap(x));
			}
			else
			{
				merge(root_odd, root_odd, new treap(x));
			}
		}
		forn(j, m)
		{
			int typ, l, r;
			scanf("%d%d%d", &typ, &l, &r);
			even_l = (l + 1) / 2;
			even_r = r / 2;
			odd_l = l / 2 + 1;
			odd_r = (r + 1) / 2;
			if (typ == 1)
				make_swap();
			else get_sum();
		}
	}
	return 0;
}