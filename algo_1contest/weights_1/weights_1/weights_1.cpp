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

const int maxn = 100;

int dp[maxn][2];
pair <bool, int> fr[maxn][2];
int k;
i64 n;

int get(int c)
{
	return (c <= k / 2 ? c : 1 + k - c);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int tests;
	scanf("%d", &tests);
	forn(test, tests)
	{
		scanf("%d%lld", &k, &n);
		dp_plus[0] = dp_minus[0] = 0;
		int p = 1;
		i64 k_pow = 1;
		while(true)
		{
			int cur = n % k;
			n /= k;
			int v1 = dp_plus[p - 1] + get(cur);
			int v2 = dp_minus[p - 1] + get(cur + 1);
			if (v1 < v2)
			{
				dp_plus[p] = v1;
				fr_plus[p] = mp(true, cur);
			}
			else
			{
				dp_plus[p] = v2;
				fr_plus[p] = mp(false, cur + 1);
			}

			int L = (p != 1 ? k - 1 - cur : k - cur);
			int v3 = dp_minus[p - 1] + get(L);
			int v4 = (L == k ? inf : dp_plus[p - 1] + get(L + 1));
			if (v3 < v4)
			{
				dp_minus[p] = v3;
				fr_minus[p] = mp(false, L);
			}
			else
			{
				dp_minus[p] = v4;
				fr_minus[p] = mp(true, L + 1);
			}
			if (n == 0)
				break;
			p++;
			k_pow = k_pow * k;
		}
		bool flag = true;
		vector <i64> answer[2];
		for (int step = p; step >= 1; step--)
		{
			int cnt = (flag ? fr_plus[step].se : fr_minus[step].se);
			if (cnt <= k / 2)
			{
				forn(c, cnt)
					answer[flag].pb(k_pow);
			}
			else
			{
				answer[flag].pb(k_pow * k);
				forn(c, k - cnt)
					answer[1 - flag].pb(k_pow);
			}
			flag = fr[step][flag].first;
			k_pow /= k;
		}
		forn(part, 2)
		{
			printf("%d ", answer[part].size());
			forn(e, answer[part].size())
				printf("%lld ", answer[part][e]);
			printf("\n");
		}
	}
	return 0;
}