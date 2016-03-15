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

const int maxn = 1e5 + 5;
i64 a[maxn];

int main()
{
	ifstream fin("qweqwe");
	freopen("addandmax.in", "r", stdin);
	freopen("addandmax.out", "w", stdout);
	int n, m;
	scanf("%d", &n);
	forn(i, n)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	forn(j, m)
	{
		char typ;
		int s, f;
		scanf("\n%c%d%d", &typ, &s, &f);
		s--;
		if (typ == 'm')
		{
			i64 ans = a[s];
			fore(j, s + 1, f - 1)
				ans = max(ans, a[j]);
			printf("%lld\n", ans);
		}
		else
		{
			int val;
			scanf("%d", &val);
			fore(j, s, f - 1)
				a[j] += val;
		}
	}

	return 0;
}