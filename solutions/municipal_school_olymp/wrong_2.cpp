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

const int maxn = 1e6 + 5;

i64 a[maxn];
int n;

inline bool check(i64 x, int the_same)
{
	return upper_bound(a, a + n, x) - lower_bound(a, a + n, x) > the_same;
}

int main()
{
#ifdef LOCAL
	freopen("gluing.in", "r", stdin);
	freopen("gluing.out", "w", stdout);
#endif
	scanf("%d", &n);
	forn(j, n)
		scanf("%lld", &a[j]);
	sort(a, a + n);
	forn(j, n)
	{
		i64 A = a[j] / 10;
		i64 B = a[j] % 10;
		i64 multiplier = 10;
		bool leading_zero = false;
		while(A > 0)
		{
			if (!leading_zero)
			{
				bool checkA = check(A, (int)(A == a[j]) + (int)(A == B));
				if (checkA)
				{
					bool checkB = check(B, 0);
					if (checkB)
					{
						printf("YES\n%lld %lld %lld", A, B, a[j]);
						exit(0);
					}
				}
			}
			leading_zero = (A % 10 == 0);
			B += multiplier * (A % 10);
			multiplier *= 10;
			A /= 10;
		}
	}
	printf("NO");
	return 0;
}