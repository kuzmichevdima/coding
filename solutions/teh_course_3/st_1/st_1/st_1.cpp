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
	int l;
	int r;
	int delta;
	node * left;
	node * right;
	node(int _l, int _r) : l(_l), r(_r), delta(0), left(NULL), right(NULL) {}
	int get_m()
	{
		return (l + r) / 2;
	}
};

struct queryStruct
{
	int typ;
	int first;
	int second;
};

typedef node * pt;
const int limit = 1e9;
const int maxn = 2e5 + 5;

vi list;
queryStruct query[maxn];

inline bool useful(int ql, int qr)
{
	return lower_bound(all(list), ql) != lower_bound(all(list), qr);
}

void update(pt & cur, int query_l, int query_r)
{
	if (cur->l == query_l && cur->r == query_r)
	{
		cur->delta++;
		return;
	}
	int m = cur->get_m();
	if (query_l < m && useful(query_l, min(query_r, m)))
	{
		if (cur->left == NULL)
			cur->left = new node(cur->l, m);
		update(cur->left, query_l, min(query_r, m));
	}
	if (query_r > m && useful(max(query_l, m), query_r))
	{
		if (cur->right == NULL)
			cur->right = new node(m, cur->r);
		update(cur->right, max(query_l, m), query_r);
	}
}

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int d = 0;
	int m;
	scanf("%d", &m);
	forn(j, m)
	{
		scanf("%d", &query[j].typ);
		if (query[j].typ == 1)
		{
			scanf("%d%d", &query[j].fi, &query[j].se);
		}
		else
		{
			scanf("%d", &query[j].fi);
			list.pb(query[j].fi);
		}
	}
	sort(all(list));
	pt root = new node(0, limit + 1);
	forn(j, m)
	{
		if (query[j].typ == 1)
		{
			int l = query[j].fi + d;
			int r = query[j].se + d;
			if (l > r)
				swap(l, r);
			assert(r <= limit);
			update(root, l, r + 1);
		}
		else
		{
			int pos = query[j].fi;
			assert(pos <= limit);
			pt cur = root;
			int answer = 0;
			while(cur != NULL)
			{
				answer += cur->delta;
				int m = cur->get_m();
				if (pos < m)
					cur = cur->left;
				else cur = cur->right;
			}
			d = answer;
			printf("%d\n", answer);
		}
	}
	return 0;
}