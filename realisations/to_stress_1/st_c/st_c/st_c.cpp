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

int tree[maxn * 4];
int start[maxn];

void update(int i, int curL, int curR, int pos, int newVal)
{
	if (curL == pos && curR == pos)
	{
		tree[i] = newVal;
		return;
	}
	int middle = (curL + curR) / 2;
	if (pos <= middle)
		update(i * 2, curL, middle, pos, newVal);
	else update(i * 2 + 1, middle + 1, curR, pos, newVal);
	tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

int get(int i, int curL, int curR, int L, int R)
{
	if (curL > R || curR < L)
		return 0;
	if (curL == L && curR == R)
	{
		return tree[i];
	}
	int middle = (curL + curR) / 2;
	int g1 = get(i * 2, curL, middle, L, min(R, middle));
	int g2 = get(i * 2 + 1, middle + 1, curR, max(middle + 1, L), R);
	return g1 + g2;
}

void build(int i, int curL, int curR)
{
	if (curL == curR)
	{
		tree[i] = start[curL];
		return;
	}
	int middle = (curL + curR) / 2;
	build(i * 2, curL, middle);
	build(i * 2 + 1, middle + 1, curR);
	tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

int main()
{
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	fore(j, 1, n)
		scanf("%d", &start[j]);
	build(1, 1, n);
	forn(it, m)
	{
		int typ;
		scanf("%d", &typ);
		if (typ == 1)
		{
			int pos, newVal;
			scanf("%d%d", &pos, &newVal);
			update(1, 1, n, pos, newVal);
		}
		else
		{
			int start, finish;
			scanf("%d%d", &start, &finish);
			int answer = get(1, 1, n, start, finish);
			printf("%d\n", answer);
		}
	}
	return 0;
}