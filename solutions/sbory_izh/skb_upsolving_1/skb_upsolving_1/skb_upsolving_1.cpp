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
typedef long longi64;

struct elem
{
	int L;
	int R;
	int number;
};

bool operator < (elem first, elem second)
{
	if (first.R != second.R)
		return first.R > second.R;
	return first.L > second.L;
}

const int maxn = 1e5 + 5;

elem a[maxn];
int n;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	forn(j, n)
	{
		scanf("%d%d", &a[j].L, &a[j].R);
		a[j].number = j + 1;
	}
	sort(a, a + n);
	forn(j, n - 1)
	{
		if (a[j].R <= a[j + 1].L)
		{
			printf("No");
			exit(0);
		}
	}
	printf("Yes\n");
	forn(j, n)
		printf("%d ", a[j].number);
	return 0;
}